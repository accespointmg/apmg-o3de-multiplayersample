/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <PlayerCoinCollectorBus.h>
#include <Source/AutoGen/MatchPlayerCoinsComponent.AutoComponent.h>

namespace MultiplayerSample
{
    class MatchPlayerCoinsComponent
        : public MatchPlayerCoinsComponentBase
    {
    public:
        AZ_MULTIPLAYER_COMPONENT(MultiplayerSample::MatchPlayerCoinsComponent, s_matchPlayerCoinsComponentConcreteUuid, MultiplayerSample::MatchPlayerCoinsComponentBase);

        static void Reflect(AZ::ReflectContext* context);
        
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;

        //! Returns the coin count (aka score) of all the players currently in game
        AZStd::vector<PlayerCoinState> GetPlayerCoinCounts() const;
    };

    class MatchPlayerCoinsComponentController
        : public MatchPlayerCoinsComponentControllerBase
        , public PlayerCoinCollectorNotificationBus::Handler
    {
    public:
        explicit MatchPlayerCoinsComponentController(MatchPlayerCoinsComponent& parent);

        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;

#if AZ_TRAIT_SERVER
        void ResetAllCoins();

        //! PlayerCoinCollectorNotificationBus overrides ...
        //! @{
        void OnPlayerCollectedCoinCountChanged(Multiplayer::NetEntityId playerEntity, uint16_t coinsCollected) override;
        void OnPlayerCollectorActivated(Multiplayer::NetEntityId playerEntity) override;
        void OnPlayerCollectorDeactivated(Multiplayer::NetEntityId playerEntity) override;
        //! }@
#endif

    private:
        // Return -1 if a state is not available for this player id
        int GetCoinStateIndex(Multiplayer::NetEntityId playerEntity) const;
    };
}
