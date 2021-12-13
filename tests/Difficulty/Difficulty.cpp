// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2017-2019, The Iridium developers
// You should have received a copy of the GNU Lesser General Public License
// If not, see <http://www.gnu.org/licenses/>.

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "CryptoNoteConfig.h"
#include "CryptoNoteCore/Difficulty.h"
#include "CryptoNoteCore/Currency.h"
#include "Logging/ConsoleLogger.h"


using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Wrong arguments" << endl;
        return 1;
    }
    Logging::ConsoleLogger logger;
    CryptoNote::CurrencyBuilder currencyBuilder(logger);
    currencyBuilder.difficultyTarget(120);
    currencyBuilder.difficultyWindow(720);
    currencyBuilder.difficultyCut(60);
    currencyBuilder.difficultyLag(15);
    CryptoNote::Currency currency = currencyBuilder.currency();
    vector<uint64_t> timestamps, cumulative_difficulties;
    fstream data(argv[1], fstream::in);
    data.exceptions(fstream::badbit);
    data.clear(data.rdstate());
    uint64_t timestamp, difficulty, cumulative_difficulty = 0;
    size_t n = 0;
    while (data >> timestamp >> difficulty) {
        size_t begin, end;
        if (n < currency.difficultyWindow() + currency.difficultyLag()) {
            begin = 0;
            end = min(n, currency.difficultyWindow());
        } else {
            end = n - currency.difficultyLag();
            begin = end - currency.difficultyWindow();
        }

//        Currency::nextDifficulty(uint8_t &version, uint32_t &blockIndex,
//                                 std::vector<uint64_t> timestamps,
//                                 std::vector<Difficulty> cumulativeDifficulties)

        uint8_t version = 5;

        uint32_t blockindex = 10;

        auto res = currency.nextDifficulty(version, blockindex,
            vector<uint64_t>(timestamps.begin() + begin, timestamps.begin() + end),
            vector<uint64_t>(cumulative_difficulties.begin() + begin, cumulative_difficulties.begin() + end));
        if (res != difficulty) {
            cerr << "Wrong difficulty for block " << n << endl
                << "Expected: " << difficulty << endl
                << "Found: " << res << endl;
            return 1;
        }
        timestamps.push_back(timestamp);
        cumulative_difficulties.push_back(cumulative_difficulty += difficulty);
        ++n;
    }
    if (!data.eof()) {
        data.clear(fstream::badbit);
    }
    return 0;
}
