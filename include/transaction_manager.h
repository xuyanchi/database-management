#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

using TransactionId = unsigned long;

struct Transaction {
    TransactionId id;
    std::vector<std::string> operations;
    bool isActive;
};

class TransactionManager {
private:
    std::map<TransactionId, std::shared_ptr<Transaction>> transactions;
    TransactionId nextTxnId;
    
public:
    TransactionManager();
    
    TransactionId createTransaction();
    void addOperation(TransactionId txnId, const std::string& operation);
    void commit(TransactionId txnId);
    void rollback(TransactionId txnId);
    bool isTransactionActive(TransactionId txnId) const;
};

#endif // TRANSACTION_MANAGER_H