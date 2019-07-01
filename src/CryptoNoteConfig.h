// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2017-2019, The Iridium developers
// You should have received a copy of the GNU Lesser General Public License
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <list>

namespace CryptoNote {
namespace parameters {

const uint32_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 0x16fa;
const uint32_t CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 20;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 525;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V5         = 30;

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;
const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V4          = 11;

// MONEY_SUPPLY - total number coins to be generated
const uint64_t MONEY_SUPPLY                                  = UINT64_C(2500000000000000);
const size_t CRYPTONOTE_COIN_VERSION                         = 1;
const unsigned EMISSION_SPEED_FACTOR                         = 18;

// mandatory mixin V4
const uint8_t MANDATORY_MIXIN_BLOCK_VERSION                  = 4;
const size_t MIN_MIXIN                                       = 2;
const size_t MAX_MIXIN                                       = 10;


static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 20000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1  = 20000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = 60000; // increasing to allow bigger tx
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 8;
const uint64_t MINIMUM_FEE                                   = UINT64_C(5000);
const uint64_t DEFAULT_DUST_THRESHOLD                        = UINT64_C(5000);

const uint64_t DIFFICULTY_TARGET                             = 175;
const uint64_t DIFFICULTY_GUESS_V5                           = 8750000; // 50kH/S
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const size_t   DIFFICULTY_WINDOW_V2                          = 60;
const size_t   DIFFICULTY_WINDOW_V4                          = 61;
const size_t   DIFFICULTY_WINDOW_V5                          = 61;
const size_t   DIFFICULTY_CUT                                = 60;
const size_t   DIFFICULTY_LAG                                = 15;
const size_t   DIFFICULTY_LAG_V2                             = 0;

static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        = 20 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;
const uint64_t MAX_TX_EXTRA_SIZE                             = 150000;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7;
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 15 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint32_t KEY_IMAGE_CHECKING_BLOCK_INDEX                = 8560;
const uint32_t IRIDIUM_REWARD_ADJUSTMENT_BLOCK               = 8560;

const uint32_t UPGRADE_HEIGHT_V2                             = 69500;
const uint32_t UPGRADE_HEIGHT_V3                             = 95250;
const uint32_t UPGRADE_HEIGHT_V4                             = 115200;
const uint32_t UPGRADE_HEIGHT_V5                             = 332500;
const unsigned UPGRADE_VOTING_THRESHOLD                      = 90;               // percent
const uint32_t UPGRADE_VOTING_WINDOW                         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
const uint32_t UPGRADE_WINDOW                                = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.bin";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.bin";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";

// testnet setup
const uint32_t TESTNET_UPGRADE_HEIGHT_V2                             = 2;
const uint32_t TESTNET_UPGRADE_HEIGHT_V3                             = 5;
const uint32_t TESTNET_UPGRADE_HEIGHT_V4                             = 10;
const uint32_t TESTNET_UPGRADE_HEIGHT_V5                             = 100;
const uint64_t TESTNET_DIFFICULTY_TARGET                             = 60; // target in testnet mode
const uint64_t TESTNET_DIFFICULTY_GUESS                              = 200;

}

const char     CRYPTONOTE_NAME[]                             = "iridium";

const uint8_t  TRANSACTION_VERSION_1                         =  1;
const uint8_t  TRANSACTION_VERSION_2                         =  2;
const uint8_t  CURRENT_TRANSACTION_VERSION                   =  TRANSACTION_VERSION_1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3;
const uint8_t  BLOCK_MAJOR_VERSION_4                         =  4;
const uint8_t  BLOCK_MAJOR_VERSION_5                         =  5;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  250;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  2000;

const int      P2P_DEFAULT_PORT                              =  12007;
const int      RPC_DEFAULT_PORT                              =  13007;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 64 * 1024 * 1024; // 64 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 100000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "8f80f9a5a434a9f1510d13336228debfee9c918ce505efe225d8c94d045fa115";

// Defaults DB configuration
const uint64_t DB_WRITE_BUFFER_MB_DEFAULT_SIZE               = 1024;          // 1 GB
const uint64_t DB_READ_BUFFER_MB_DEFAULT_SIZE                = 1024;          // 1 GB
const uint32_t DB_DEFAULT_MAX_OPEN_FILES                     = 500;           // 500 files
const uint16_t DB_DEFAULT_BACKGROUND_THREADS_COUNT           = 10;            // 10 threads

const char* const SEED_NODES[] = {
    "144.208.96.2:12001", /*EXP*/
    "5.178.66.70:12001", /*AMS*/
    "192.99.8.12:12007", /*MTL*/
    "139.99.131.92:12017", /*SDN*/
    "139.99.131.92:12018",
    "139.99.131.92:12019",
    "139.99.131.92:12020",
};


struct CheckpointData {
    uint32_t index;
    const char* blockId;
};

// checkpoints at Hardforks
const std::initializer_list<CheckpointData> CHECKPOINTS = {
    {69500,"1e6f58fac635e3e0a0ca3845f6a07abaf4080c36dd91bfab315f6cdb657cc775"},
    {95250,"a5d8f703b1e4afa73b9f3050b9972c2b23730fcb5c916b521bc7d6ce2ad4c959"},
    {115200,"896c2d44deca8b1349e55f88ee8795d51bfc7b0feb4a59562fda61ae6e1f9fa5"},
    {319000,"3e1b3f7decdf3ffc7d40ca67dc7cbab464247f54d83f0f3ea33216c29a65530d"}
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS
