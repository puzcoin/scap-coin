// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2020 The SafeCapital Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */


static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("000001629e0fdcc040200240aff8b6672fe28d3c7f2539b0169c08bd6306ff4e"))
    (455, uint256("0cb023398ff879c497dff568b558029e0fd2614750448e1c5e7c2e213d077b93"))   
    (3335, uint256("242ba8255f4be2fb878cdbcd7ad7748394e1e82034c21adc36fde3be4edf3529"))    
    (44860, uint256("1909e1099507e45324213da2619ee896539e2e68d92f43ba1f163796682c846c"))     
    (103100, uint256("dcf864e07fe3e6b7da064d02ef4a464b27d162784a84f9b30f8ff2c6b12ac3f6"));    
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1579683683,   // * UNIX timestamp of last checkpoint block
    213985,        // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    2000          // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0000068b968b7882b0605e8f6d602cdd1bdc885f1cbdfc4861d93bb7a5d8cfd4"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1573452000,
    0,
    5};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1573452000,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0xf8;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0xb1;
        vAlertPubKey = ParseHex("041466b15d2c03026d41e342de7c1e063d48e3f7f351e94b68fce0ebcd23c7b15b8fea3368b8ab2bdecb6cf2af116420430163d6a76f12a56fc692687a8b279424");
        nDefaultPort = 47002;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // SafeCapital starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 525600; // one year
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SafeCapital: every block
        nTargetSpacing = 1 * 60;  // SafeCapital: 1 minute
        nLastPOWBlock = 210;
        nMaturity = 100;
        nCollateralMaturity = 525600;
        nCollateralMaturityEnforcementHeight = 1000;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 10100000 * COIN;
        nMasternodeCollateral = 1000.00019; 
        nStakeMinConfirmations = 300;   // Required number of confirmations
        nStakeMinAmount = 100 * COIN;   // Minimum required staking amount

        const char* pszTimestamp = "It’s money 2.0, a huge huge huge deal.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("049ca629c0fc0b794aa891ab3b137c1b7de5c347d54bbf755a8e2584a2b12ae295e41909e0a7422c9335d416514a482da27682f0699865dd8a1f31894cbd7aa184") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1573452000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1577121;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001629e0fdcc040200240aff8b6672fe28d3c7f2539b0169c08bd6306ff4e"));
        assert(genesis.hashMerkleRoot == uint256("0x191f4c9a2c07b8140332f6060d027913ea806b35f7db02d7bcfe5f0f82e88ec8"));

     // vSeeds.push_back(CDNSSeedData("node1", "node1.safecapital.io"));
	vSeeds.push_back(CDNSSeedData("node1", "45.249.244.140"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); // Safecapital addresses start with 'C'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 10); // Safecapital script addresses start with '5'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 135);    // Safecapital private keys start with 'w'
		// SafeCapital BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		// SafeCapital BIP32 pubkeys start with 'xprv' (Bitcoin defaults)		
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is '0X80000a00' from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x0a)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "042e6d963c11165f9b70fd229abdfd20412060bfbd4b42c2c847a7370fa85035fb690c4754d7d20095ee97d7fcf0238a0a26575b5fc183d3576242788dc70ec9f8";
        strPrivatesendPoolDummyAddress = "CQ4fj33mJBaxMWcxjAz9GP8pJ7vZfQRxju";
        nStartMasternodePayments = 1573452000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0xf7;
        pchMessageStart[2] = 0x91;
        pchMessageStart[3] = 0xfa;
        vAlertPubKey = ParseHex("04064265c22981ab56d931b575e25360235a2b0972857f5982bc5c495a7c618b614475f9b862c69cce8e6aa6a582eba141a3352b6f1eda26641be817f07720b097");
        nDefaultPort = 47004;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SafeCapital: 1 day
        nTargetSpacing = 1 * 60;  // SafeCapital: 1 minute
        nLastPOWBlock = 210;
        nMaturity = 100;
        nCollateralMaturity = 300;
        nCollateralMaturityEnforcementHeight = 1000;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nMasternodeCollateral = 1000.00019; 
        nStakeMinConfirmations = 15;   // Required number of confirmations
        nStakeMinAmount = 10 * COIN;    // Minimum required staking amount

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1573452000;
        genesis.nNonce = 1844489;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000068b968b7882b0605e8f6d602cdd1bdc885f1cbdfc4861d93bb7a5d8cfd4"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("node1", "node1.safecapital.io"));
        vSeeds.push_back(CDNSSeedData("node2", "node2.safecapital.io"));
        vSeeds.push_back(CDNSSeedData("node3", "node3.safecapital.io"));
        vSeeds.push_back(CDNSSeedData("node4", "node4.safecapital.io"));
        vSeeds.push_back(CDNSSeedData("node5", "node5.safecapital.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127); // Testnet safecapital addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);  // Testnet safecapital script addresses start with '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
		// SafeCapital BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		// SafeCapital BIP32 pubkeys start with 'xprv' (Bitcoin defaults)		
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Testnet safecapital BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "042653babb9cd2ddc8222c14112fea41715c4b009bd461b6150d09718ab43720ca941fad5166c706f1286741686fc9206e2e80de4e1b37fe452bdad942e5bd9d47";
        strPrivatesendPoolDummyAddress = "CQ4fj33mJBaxMWcxjAz9GP8pJ7vZfQRxju";
        nStartMasternodePayments = 1573452000;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0x3b;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0xc3;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // SafeCapital: 1 day
        nTargetSpacing = 1 * 60;        // SafeCapital: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1573452000;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2048;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 47006;
        assert(hashGenesisBlock == uint256("0x36b241e8bf3675c0323cf1671be3a234dfe325ba404a1cfec433e27c90a95be7"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 47008;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
