#include <ImGuiNotify.hpp>

#include "../../Modules.h"
#include <ImGui/imgui.h>
#include <thread>

#include "../../../Cache/Cache.h"

enum LegacyMushroomStage
{
    IDLE = 0,
    RIGHT_LEFT = 1,
    LEFT_RIGHT = 2,
    SWITCH_SIDE = 3,
    REPLACE = 4
};

const std::string GOLD_BLOCK_ID = "minecraft:gold_block";
const std::string EMERALD_BLOCK_ID = "minecraft:emerald_block";
const std::string DIAMOND_BLOCK_ID = "minecraft:diamond_block";
const std::string REDSTONE_BLOCK_ID = "minecraft:redstone_block";

void Ripterms::Modules::MushroomAutomation::run()
{
    if (!enabled)
        return;

    if (cache->gameSettings.getPauseOnLostFocus())
    {
        cache->gameSettings.setPauseOnLostFocus(false);
    }
    
    if (stage == IDLE)
    {
        if (!cache->thePlayer.isOnGround())
        {
            ImGui::InsertNotification({ImGuiToastType::Warning, 3000, "You must be on the ground to start the automation"});
            enabled = false;
            return;
        }
        
        Block block = getBlockBelowPlayer();

        if (!block.isBlock(GOLD_BLOCK_ID))
        {
            ImGui::InsertNotification({ImGuiToastType::Warning, 3000, "You must be on a gold block to start the automation"});
            enabled = false;
            return;
        }

        Maths::Vector3d pos = cache->thePlayer.getPosition();
        startBlockPos = {pos.x, pos.y - 1, pos.z};

        stage = LEFT_RIGHT;
    }
    
    cache->entityRenderer.getMouseOver(1.0f);
    cache->theMinecraft.setLeftClickCounter(-1);
    cache->theMinecraft.sendClickBlockToController(true);

    preventStuck();
    runStage();
}

void Ripterms::Modules::MushroomAutomation::disable()
{
    stage = IDLE;
    
    cache->gameSettings.getKeyBindAttack().setPressed(false);
    cache->gameSettings.getKeyBindLeft().setPressed(false);
    cache->gameSettings.getKeyBindRight().setPressed(false);
    cache->gameSettings.getKeyBindForward().setPressed(false);
    cache->gameSettings.getKeyBindBack().setPressed(false);

    cache->gameSettings.setPauseOnLostFocus(true);
}

void Ripterms::Modules::MushroomAutomation::renderGUI()
{
    ImGui::Checkbox("Legacy Mushroom automation", &enabled);

    ImGui::BeginGroup();
    ImGui::SliderFloat("Yaw", &yaw, -180.0f, 180.0f, "%.1f");
    ImGui::SliderFloat("Pitch", &pitch, -90.0f, 90.0f, "%.1f");
    ImGui::EndGroup();
}

void Ripterms::Modules::MushroomAutomation::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
    if (!enabled || !this_player.isOnGround())
        return;

    if (stage != REPLACE)
        this_player.setRotation({yaw, pitch});
    
    Block block = getBlockBelowPlayer();

    evaluateStage(block);
}

void Ripterms::Modules::MushroomAutomation::evaluateStage( Block& belowBlock)
{
    if (stage == IDLE)
        return;

    if (belowBlock.isBlock(EMERALD_BLOCK_ID))
        stage = SWITCH_SIDE;

    if (belowBlock.isBlock(DIAMOND_BLOCK_ID))
        stage = LEFT_RIGHT;

    if (belowBlock.isBlock(GOLD_BLOCK_ID))
        stage = RIGHT_LEFT;
    
    if (belowBlock.isBlock(REDSTONE_BLOCK_ID))
    {
        stage = REPLACE;
    }
}

void Ripterms::Modules::MushroomAutomation::runStage()
{
    switch (stage)
    {
        case RIGHT_LEFT:
            clearOtherKeys(stage);
            cache->gameSettings.getKeyBindLeft().setPressed(true);
            break;
        case LEFT_RIGHT:
            clearOtherKeys(stage);
            cache->gameSettings.getKeyBindRight().setPressed(true);
            break;
        case SWITCH_SIDE:
            clearOtherKeys(stage);
            cache->gameSettings.getKeyBindBack().setPressed(true);
            break;
        case REPLACE:
            clearOtherKeys(stage);
            replaceOnStart();
            break;
    }
}

void Ripterms::Modules::MushroomAutomation::clearOtherKeys(int currentStage)
{
    switch (currentStage)
    {
        case RIGHT_LEFT:
            cache->gameSettings.getKeyBindRight().setPressed(false);
            cache->gameSettings.getKeyBindBack().setPressed(false);
            break;
        case LEFT_RIGHT:
            cache->gameSettings.getKeyBindLeft().setPressed(false);
            cache->gameSettings.getKeyBindForward().setPressed(false);
            break;
        case SWITCH_SIDE:
            cache->gameSettings.getKeyBindRight().setPressed(false);
            cache->gameSettings.getKeyBindForward().setPressed(false);
            break;
        case REPLACE:
            cache->gameSettings.getKeyBindLeft().setPressed(false);
            cache->gameSettings.getKeyBindRight().setPressed(false);
            cache->gameSettings.getKeyBindBack().setPressed(false);
            break;
    }
}

void Ripterms::Modules::MushroomAutomation::evaluateStageStrict( Block& belowBlock)
{
    if (stage == IDLE)
        return;

    switch (stage)
    {
    case RIGHT_LEFT:
        if (belowBlock.isBlock(EMERALD_BLOCK_ID))
            stage = SWITCH_SIDE;
        break;
    case SWITCH_SIDE:
        if (belowBlock.isBlock(DIAMOND_BLOCK_ID))
            stage = LEFT_RIGHT;
        break;
    case LEFT_RIGHT:
        if (belowBlock.isBlock(GOLD_BLOCK_ID))
            stage = RIGHT_LEFT;
        else if (belowBlock.isBlock(REDSTONE_BLOCK_ID))
            stage = REPLACE;
        break;
    case REPLACE:
        if (belowBlock.isBlock(DIAMOND_BLOCK_ID))
            stage = RIGHT_LEFT;
        else if (belowBlock.isBlock(REDSTONE_BLOCK_ID))
            stage = IDLE;
        break;
    }
}

void Ripterms::Modules::MushroomAutomation::replaceOnStart()
{
    static auto lastReplaceTime = std::chrono::steady_clock::now();
    static bool isReplaceActive = false;
    static int replaceStage = -1;

    auto currentTime = std::chrono::steady_clock::now();

    if (replaceStage == -1)
    {
        lastReplaceTime = currentTime;
        replaceStage = 0;
    }
    
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastReplaceTime);

    cache->thePlayer.setRotation({-91.0f, pitch});
    
    switch (replaceStage)
    {
    case 0:
        if (elapsedTime.count() >= 1000 && !isReplaceActive)
        {
            cache->gameSettings.getKeyBindJump().setPressed(true);
            cache->thePlayer.setFlying(true);
            isReplaceActive = true;
            lastReplaceTime = currentTime;
            replaceStage = 1;
        }
        break;
    case 1:
        if (cache->thePlayer.getPosition().y >= startBlockPos.y + 3.0f)
        {
            cache->gameSettings.getKeyBindJump().setPressed(false);
            cache->gameSettings.getKeyBindForward().setPressed(true);
            lastReplaceTime = currentTime;
            replaceStage = 2;
        }
        else if (elapsedTime.count() >= 200)
        {
            lastReplaceTime = currentTime;
        }
        break;
    case 2:
        if (cache->thePlayer.getPosition().x >= startBlockPos.x - 3.0f)
        {
            cache->gameSettings.getKeyBindForward().setPressed(false);
            cache->thePlayer.setFlying(false);
            lastReplaceTime = currentTime;
            replaceStage = 3;
        }
        else if (elapsedTime.count() >= 1)
        {
            lastReplaceTime = currentTime;
        }
        break;
    case 3:
        if (elapsedTime.count() >= 500)
        {
            lastReplaceTime = currentTime;
            isReplaceActive = false;
            replaceStage = -1;
        }
        break;
    default: break;
    }
}

void Ripterms::Modules::MushroomAutomation::preventStuck()
{
    static auto lastPreventStuckTime = std::chrono::steady_clock::now();
    static bool isPreventStuckActive = false;

    if (stage != IDLE && stage != REPLACE)
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastPreventStuckTime);

        switch (stage)
        {
        case RIGHT_LEFT:
            if (elapsedTime.count() >= 1000 && !isPreventStuckActive)
            {
                cache->gameSettings.getKeyBindForward().setPressed(true);
                isPreventStuckActive = true;
                lastPreventStuckTime = currentTime;
            }
            else if (isPreventStuckActive && elapsedTime.count() >= 100)
            {
                cache->gameSettings.getKeyBindForward().setPressed(false);
                isPreventStuckActive = false;
            }
            break;
        case SWITCH_SIDE:
            if (elapsedTime.count() >= 200 && !isPreventStuckActive)
            {
                cache->gameSettings.getKeyBindLeft().setPressed(true);
                isPreventStuckActive = true;
                lastPreventStuckTime = currentTime;
            }
            else if (isPreventStuckActive && elapsedTime.count() >= 100)
            {
                cache->gameSettings.getKeyBindLeft().setPressed(false);
                isPreventStuckActive = false;
            }
            break;
        case LEFT_RIGHT:
            if (elapsedTime.count() >= 1000 && !isPreventStuckActive)
            {
                cache->gameSettings.getKeyBindBack().setPressed(true);
                isPreventStuckActive = true;
                lastPreventStuckTime = currentTime;
            }
            else if (isPreventStuckActive && elapsedTime.count() >= 100)
            {
                cache->gameSettings.getKeyBindBack().setPressed(false);
                isPreventStuckActive = false;
            }
            break;
        }
    }
}


void Ripterms::Modules::MushroomAutomation::toggleFly()
{
    cache->gameSettings.getKeyBindJump().setPressed(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    cache->gameSettings.getKeyBindJump().setPressed(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cache->gameSettings.getKeyBindJump().setPressed(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    cache->gameSettings.getKeyBindJump().setPressed(false);
}

Block Ripterms::Modules::MushroomAutomation::getBlockBelowPlayer()
{
    Maths::Vector3d pos = cache->thePlayer.getPosition();
    return cache->theWorld.getBlock({pos.x, pos.y - 1, pos.z});
}