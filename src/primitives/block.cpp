// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "hash.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "crypto/common.h"
#include "crypto/sha256_y.h"

using namespace sha256_y;

void skein_hash(const char* input, char* output, uint32_t len)
{
    char temp[64];

    sph_skein512_context ctx_skien;
    sph_skein512_init(&ctx_skien);
    sph_skein512(&ctx_skien, input, len);
    sph_skein512_close(&ctx_skien, &temp);

    SHA256_CTX ctx_sha256;
    SHA256_Init(&ctx_sha256);
    SHA256_Update(&ctx_sha256, &temp, 64);
    SHA256_Final((unsigned char*) output, &ctx_sha256);
}

uint256 CBlockHeader::GetHash() const
{
    uint256 thash;
    uint32_t len = (END(nNonce) - BEGIN(nVersion))*sizeof(BEGIN(nVersion)[0]);
    skein_hash(&BEGIN(nVersion)[0], (char *) &thash, len);
    return thash;
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++)
    {
        s << "  " << vtx[i].ToString() << "\n";
    }
    return s.str();
}
