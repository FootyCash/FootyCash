// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHAIN_PARAMS_H
#define BITCOIN_CHAIN_PARAMS_H

#include "bignum.h"
#include "uint256.h"
#include "util.h"

#include <vector>

using namespace std;

#define MESSAGE_START_SIZE 4
typedef unsigned char MessageStartChars[MESSAGE_START_SIZE];

class CAddress;
class CBlock;

struct CDNSSeedData {
    string name, host;
    CDNSSeedData(const string &strName, const string &strHost) : name(strName), host(strHost) {}
};

/**
 * CChainParams defines various tweakable parameters of a given instance of the
 * Bitcoin system. There are three: the main network on which people trade goods
 * and services, the public test network which gets reset from time to time and
 * a regression test mode which is intended for private networks only. It has
 * minimal difficulty to ensure that blocks can be found instantly.
 */
class CChainParams
{
public:
    enum Network {
        MAIN,
        TESTNET,
        REGTEST,

        MAX_NETWORK_TYPES
    };

    enum Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,
        EXT_PUBLIC_KEY,
        EXT_SECRET_KEY,

        MAX_BASE58_TYPES
    };

    const uint256& HashGenesisBlock() const { return hashGenesisBlock; }
    const MessageStartChars& MessageStart() const { return pchMessageStart; }
    const vector<unsigned char>& AlertKey() const { return vAlertPubKey; }
    int GetDefaultPort() const { return nDefaultPort; }
    const CBigNum& ProofOfWorkLimit() const { return bnProofOfWorkLimit; }
    int SubsidyHalvingInterval() const { return nSubsidyHalvingInterval; }
    virtual const CBlock& GenesisBlock() const = 0;
    virtual bool RequireRPCPassword() const { return true; }
    const string& DataDir() const { return strDataDir; }
    virtual Network NetworkID() const = 0;
    const vector<CDNSSeedData>& DNSSeeds() const { return vSeeds; }
    const std::vector<unsigned char> &Base58Prefix(Base58Type type) const { return base58Prefixes[type]; }
    virtual const vector<CAddress>& FixedSeeds() const = 0;
    int RPCPort() const { return nRPCPort; }

    inline bool TestNet() const { return NetworkID() == CChainParams::TESTNET; }

    int CoinbaseMaturity() const { return nCoinbaseMaturity; }
    int StakeMinConfirmations() const { return nStakeMinConfirmations; }

    CBigNum ProofOfStakeLimit() const { return bnProofOfStakeLimit; }

    unsigned int StakeMinAge() const { return nStakeMinAge; }
    unsigned int ModifierInterval() const { return nModifierInterval; }
    
    int64_t StakeCoinYearReward() const { return nStakeCoinYearReward; }
    int PoWHalfLife() const { return nPoWHalving;}
    int PoSHalfLife() const { return nPoSHalving;}
    int LastPOWBlock() const { return nLastPOWBlock; }
    int FirstPoSBlock() const { return nFirstPoSBlock; }
    int MinDelay() const { return nMinDelay; }
    int TargetSpacing() const { return nTargetSpacing; }
    int64_t LaunchTime() const { return nLaunchTime; }
    int64_t BasicPoWReward() const { return nBasicPoWReward; }

    int PoSGranularity() const { return nPoSGranularity;}
    
    const vector<unsigned char>& GetCheckpointPubKey() const {return vchSyncCheckpointPubKey;}

    inline int64_t FutureDrift(int64_t nTime, int nHeight) const { return nTime + 10 * 60; }

    inline unsigned int GetTargetSpacing(int nHeight) const { return nTargetSpacing; }

    int64_t MaxMoney() const { return nMaxMoney; }
    
protected:
    CChainParams() {};

    uint256 hashGenesisBlock;
    MessageStartChars pchMessageStart;
    // Raw pub key bytes for the broadcast alert signing key.
    vector<unsigned char> vAlertPubKey;
    vector<unsigned char>  vchSyncCheckpointPubKey;
    int nDefaultPort;
    int nRPCPort;
    CBigNum bnProofOfWorkLimit;
    int nSubsidyHalvingInterval;
    string strDataDir;
    vector<CDNSSeedData> vSeeds;
    std::vector<unsigned char> base58Prefixes[MAX_BASE58_TYPES];

    CBigNum bnProofOfStakeLimit;

    // Chain
    int nTargetSpacing;
    int64_t nBasicPoWReward;
    int nCoinbaseMaturity;
    int64_t nLaunchTime;
    

    // PoW section
    int nLastPOWBlock;
    int nPoWHalving;

    // PoS section
    int nPoSGranularity;
    int nPoSHalving;
    int nMinDelay;
    int nFirstPoSBlock;
    int64_t nStakeCoinYearReward;
    unsigned int nStakeMinAge;
    // MODIFIER_INTERVAL: time to elapse before new modifier is computed
    unsigned int nModifierInterval;
    int nStakeMinConfirmations;


    int64_t nMaxMoney;

};

/**
 * Return the currently selected parameters. This won't change after app startup
 * outside of the unit tests.
 */
const CChainParams &Params();

/** Sets the params returned by Params() to those for the given network. */
void SelectParams(CChainParams::Network network);

/**
 * Looks for -regtest or -testnet and then calls SelectParams as appropriate.
 * Returns false if an invalid combination is given.
 */
bool SelectParamsFromCommandLine();

inline bool TestNet() {
    // Note: it's deliberate that this returns "false" for regression test mode.
    return Params().NetworkID() == CChainParams::TESTNET;
}

#endif
