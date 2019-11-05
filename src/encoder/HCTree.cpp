/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"
#include <queue>
#include <stack>

/* TODO */
HCTree::~HCTree() { deleteAll(root); }
/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {
    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> sets;

    for (unsigned int i = 0; i < freqs.size(); i++) {
        if (freqs[i] > 0) {
            HCNode* temp = new HCNode(freqs[i], i, 0, 0, 0);
            leaves[i] = temp;
            sets.push(temp);
        }
    }
    HCNode* parent = nullptr;
    HCNode* right = nullptr;
    HCNode* left = nullptr;
    HCNode* temp = nullptr;

    while (sets.size() > 1) {
        left = sets.top();
        sets.pop();

        right = sets.top();
        sets.pop();

        if (left->symbol > right->symbol) {
            parent = new HCNode((left->count) + (right->count), left->symbol,
                                left, right, 0);
        } else {
            parent = new HCNode((left->count) + (right->count), right->symbol,
                                left, right, 0);
        }

        right->p = parent;
        left->p = parent;

        sets.push(parent);
    }
    root = sets.top();
    root->p = nullptr;
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* curr = leaves[symbol];
    stack<int> result;

    while (curr != nullptr && curr->p != nullptr) {
        if (curr->p->c0 == curr) {
            result.push(0);
        } else {
            result.push(1);
        }
        curr = curr->p;
    }
    while (!result.empty()) {
        out << result.top();
        result.pop();
    }
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const {
    HCNode* curr = root;
    byte input;
    while (curr->c0 != nullptr && curr->c1 != nullptr) {
        input = in.get();
        if (input == '0') {
            curr = curr->c0;
        } else if (input == '1') {
            curr = curr->c1;
        } else {
            return 0;
        }
    }
    return curr->symbol;
}

void HCTree::deleteAll(HCNode* node) {
    if (node->c0) {
        deleteAll(node->c0);
    }
    if (node->c1) {
        deleteAll(node->c1);
    }
    delete node;
}
