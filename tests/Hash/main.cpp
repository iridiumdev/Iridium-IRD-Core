// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2017-2019, The Iridium developers
// You should have received a copy of the GNU Lesser General Public License
// If not, see <http://www.gnu.org/licenses/>.

#include <cstddef>
#include <fstream>
#include <iomanip>
#include <ios>
#include <string>

#include "crypto/hash.h"
#include "../Io.h"

using namespace std;
typedef Crypto::Hash chash;

//Crypto::cn_context *context;

extern "C" {
#ifdef _MSC_VER
#pragma warning(disable: 4297)
#endif

  static void hash_tree(const void *data, size_t length, char *hash) {
    if ((length & 31) != 0) {
      throw ios_base::failure("Invalid input length for tree_hash");
    }
    Crypto::tree_hash((const char (*)[32]) data, length >> 5, hash);
  }

  static void cn_pico_slow_hash_v0(const void *data, size_t length, char *hash) {
    Crypto::cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 0, 0, CN_PICO_PAGE_SIZE, CN_PICO_SCRATCHPAD, CN_PICO_ITERATIONS);
  }

  static void slow_hash(const void *data, size_t length, char *hash) {
    Crypto::cn_slow_hash_v0(data, length, *reinterpret_cast<chash *>(hash));
  }
}


// Standard Cryptonight Definitions
//inline void cn_slow_hash_v0(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 0, 0, 0, CN_PAGE_SIZE, CN_SCRATCHPAD, CN_ITERATIONS);
//}

//inline void cn_slow_hash_v1(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 0, 1, 0, CN_PAGE_SIZE, CN_SCRATCHPAD, CN_ITERATIONS);
//}

//inline void cn_slow_hash_v2(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 0, 2, 0,  CN_PAGE_SIZE, CN_SCRATCHPAD, CN_ITERATIONS);
//}


// Standard Cryptonight Lite Definitions
//inline void cn_lite_slow_hash_v0(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 0, 0, CN_LITE_PAGE_SIZE, CN_LITE_SCRATCHPAD, CN_LITE_ITERATIONS);
//}

//inline void cn_lite_slow_hash_v1(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 1, 0, CN_LITE_PAGE_SIZE, CN_LITE_SCRATCHPAD, CN_LITE_ITERATIONS);
//}

//inline void cn_lite_slow_hash_v2(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 2, 0, CN_LITE_PAGE_SIZE, CN_LITE_SCRATCHPAD, CN_LITE_ITERATIONS);
//}

// Standard Cryptonight lite Pico/Trtl
//inline void cn_pico_slow_hash_v0(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 0, 0, CN_PICO_PAGE_SIZE, CN_PICO_SCRATCHPAD, CN_PICO_ITERATIONS);
//}

//inline void cn_pico_slow_hash_v1(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 1, 0, CN_PICO_PAGE_SIZE, CN_PICO_SCRATCHPAD, CN_PICO_ITERATIONS);
//}

//inline void cn_pico_slow_hash_v2(const void *data, size_t length, Hash &hash) {
//  cn_slow_hash(data, length, reinterpret_cast<char *>(&hash), 1, 2, 0, CN_PICO_PAGE_SIZE, CN_PICO_SCRATCHPAD, CN_PICO_ITERATIONS);
//}

//inline void tree_hash(const Hash *hashes, size_t count, Hash &root_hash) {
//  tree_hash(reinterpret_cast<const char (*)[HASH_SIZE]>(hashes), count, reinterpret_cast<char *>(&root_hash));
//}

//inline void tree_branch(const Hash *hashes, size_t count, Hash *branch) {
//  tree_branch(reinterpret_cast<const char (*)[HASH_SIZE]>(hashes), count, reinterpret_cast<char (*)[HASH_SIZE]>(branch));
//}

//inline void tree_hash_from_branch(const Hash *branch, size_t depth, const Hash &leaf, const void *path, Hash &root_hash) {
//  tree_hash_from_branch(reinterpret_cast<const char (*)[HASH_SIZE]>(branch), depth, reinterpret_cast<const char *>(&leaf), path, reinterpret_cast<char *>(&root_hash));
//}

extern "C" typedef void hash_f(const void *, size_t, char *);
struct hash_func {
  const string name;
  hash_f &f;
} hashes[] = {{"fast", Crypto::cn_fast_hash}, {"slow", slow_hash}, {"tree", hash_tree},
  {"extra-blake", Crypto::hash_extra_blake}, {"extra-groestl", Crypto::hash_extra_groestl},
  {"extra-jh", Crypto::hash_extra_jh}, {"extra-skein", Crypto::hash_extra_skein}};

int main(int argc, char *argv[]) {
  hash_f *f;
  hash_func *hf;
  fstream input;
  vector<char> data;
  chash expected, actual;
  size_t test = 0;
  bool error = false;
  if (argc != 3) {
    cerr << "Wrong number of arguments" << endl;
    return 1;
  }
  for (hf = hashes;; hf++) {
    if (hf >= &hashes[sizeof(hashes) / sizeof(hash_func)]) {
      cerr << "Unknown function" << endl;
      return 1;
    }
    if (argv[1] == hf->name) {
      f = &hf->f;
      break;
    }
  }
//  if (f == slow_hash) {
//    context = new Crypto::cn_context();
//  }
  input.open(argv[2], ios_base::in);
  for (;;) {
    ++test;
    input.exceptions(ios_base::badbit);
    get(input, expected);
    if (input.rdstate() & ios_base::eofbit) {
      break;
    }
    input.exceptions(ios_base::badbit | ios_base::failbit | ios_base::eofbit);
    input.clear(input.rdstate());
    get(input, data);
    f(data.data(), data.size(), (char *) &actual);
    if (expected != actual) {
      size_t i;
      cerr << "Hash mismatch on test " << test << endl << "Input: ";
      if (data.size() == 0) {
        cerr << "empty";
      } else {
        for (i = 0; i < data.size(); i++) {
          cerr << setbase(16) << setw(2) << setfill('0') << int(static_cast<unsigned char>(data[i]));
        }
      }
      cerr << endl << "Expected hash: ";
      for (i = 0; i < 32; i++) {
          cerr << setbase(16) << setw(2) << setfill('0') << int(reinterpret_cast<unsigned char *>(&expected)[i]);
      }
      cerr << endl << "Actual hash: ";
      for (i = 0; i < 32; i++) {
          cerr << setbase(16) << setw(2) << setfill('0') << int(reinterpret_cast<unsigned char *>(&actual)[i]);
      }
      cerr << endl;
      error = true;
    }
  }
  return error ? 1 : 0;
}
