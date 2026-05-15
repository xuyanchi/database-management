#include "transaction_manager.h"
#include <iostream>

TransactionManager::TransactionManager() : nextTxnId(1) {}

TransactionId TransactionManager::createTransaction() {
    auto txn = std::make_shared<Transaction>();
    txn->id = nextTxnId;
    txn->isActive = true;
    
    transactions[nextTxnId] = txn;
    std::cout << "Transaction " << nextTxnId << " created" << std::endl;
    
    return nextTxnId++;
}

void TransactionManager::addOperation(TransactionId txnId, const std::string& operation) {
    if (transactions.find(txnId) != transactions.end()) {
        transactions[txnId]->operations.push_back(operation);
    }
}

void TransactionManager::commit(TransactionId txnId) {
    if (transactions.find(txnId) != transactions.end()) {
        transactions[txnId]->isActive = false;
        std::cout << "Transaction " << txnId << " committed" << std::endl;
    }
}

void TransactionManager::rollback(TransactionId txnId) {
    if (transactions.find(txnId) != transactions.end()) {
        transactions.erase(txnId);
        std::cout << "Transaction " << txnId << " rolled back" << std::endl;
    }
}

bool TransactionManager::isTransactionActive(TransactionId txnId) const {
    if (transactions.find(txnId) != transactions.end()) {
        return transactions.at(txnId)->isActive;
    }
    return false;
}