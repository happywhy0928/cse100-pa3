/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"

/* TODO */
HCTree::~HCTree() {}

/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }

void deleteAll(HCNode* node) {
    if (node->c0) {
        deleteAll(node->c0);
    }
    if (node->c1) {
        deleteAll(node->c1);
    }
    delete node;
}
