# C++ Database Management System

一个功能完整的C++数据库管理系统，支持CRUD操作、SQL查询、索引和事务管理。

## 功能特性

✅ **CRUD操作** - 完整的创建、读取、更新、删除功能
✅ **SQL查询** - SELECT、INSERT、UPDATE、DELETE语句支持
✅ **B树索引** - 高效的数据查询加速
✅ **事务管理** - ACID属性支持（原子性、一致性、隔离性、持久性）
✅ **文件系统存储** - 数据持久化到磁盘
✅ **交互式菜单** - 便捷的命令行界面

## 项目结构

```
database-management/
├── include/                    # 头文件目录
│   ├── database.h             # 主数据库类
│   ├── table.h                # 表类
│   ├── index.h                # B树索引类
│   ├── query_executor.h       # SQL查询执行器
│   ├── transaction_manager.h  # 事务管理器
│   └── storage_engine.h       # 存储引擎
├── src/                        # 源文件目录
│   ├── main.cpp               # 主程序
│   ├── database.cpp           # 数据库实现
│   ├── table.cpp              # 表实现
│   ├── index.cpp              # 索引实现
│   ├── query_executor.cpp     # 查询执行器
│   ├── transaction_manager.cpp # 事务管理
│   └── storage_engine.cpp     # 存储引擎
├── CMakeLists.txt             # CMake构建配置
└── README.md                  # 本文档
```

## 编译和运行

### 前置条件
- C++17或更高版本
- CMake 3.10或更高版本
- GCC/Clang/MSVC编译器

### 编译步骤

```bash
# 克隆仓库
git clone https://github.com/xuyanchi/database-management.git
cd database-management

# 创建构建目录
mkdir build
cd build

# 使用CMake构建
cmake ..
make

# 运行程序
./database_manager
```

### Windows编译

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build .
./Release/database_manager.exe
```

## 使用示例

### 交互式菜单

程序启动后会显示以下菜单：

```
=== C++ Database Management System ===
1. Create Table
2. Insert Data
3. Query Data
4. Update Data
5. Delete Data
6. Create Index
7. Execute SQL
8. Begin Transaction
9. Exit
======================================
```

### 代码示例

```cpp
#include "database.h"

int main() {
    // 创建数据库实例
    Database db("./mydata");

    // 创建表
    db.createTable("users", {
        {"id", "INT"},
        {"name", "STRING"},
        {"email", "STRING"}
    });

    // 插入数据
    Row user;
    user["id"] = "1";
    user["name"] = "John Doe";
    user["email"] = "john@example.com";
    db.insert("users", user);

    // 创建索引
    db.createIndex("users", "id");

    // 查询数据
    auto results = db.select("users");
    for (const auto& row : results) {
        std::cout << "Name: " << row.at("name") << std::endl;
    }

    // 更新数据
    Row updates;
    updates["name"] = "Jane Doe";
    db.update("users", "id = 1", updates);

    // 事务处理
    auto txn = db.beginTransaction();
    Row newUser;
    newUser["id"] = "2";
    newUser["name"] = "Jane Smith";
    newUser["email"] = "jane@example.com";
    db.insert("users", newUser);
    db.commit(txn);

    // 删除数据
    db.deleteRow("users", "id = 2");

    return 0;
}
```

## 核心类说明

### Database 类
主数据库类，管理所有表和事务。

**主要方法：**
- `createTable()` - 创建新表
- `dropTable()` - 删除表
- `insert()` - 插入数据
- `select()` - 查询数据
- `update()` - 更新数据
- `deleteRow()` - 删除数据
- `createIndex()` - 创建索引
- `query()` - 执行SQL查询
- `beginTransaction()` - 开始事务
- `commit()` - 提交事务
- `rollback()` - 回滚事务

### Table 类
表的实现类，管理行数据和索引。

**主要方法：**
- `insertRow()` - 插入一行
- `searchRows()` - 查询行
- `updateRows()` - 更新行
- `deleteRows()` - 删除行

### BTreeIndex 类
B树索引的实现。

**主要方法：**
- `insert()` - 插入索引项
- `remove()` - 删除索引项
- `search()` - 搜索索引

### TransactionManager 类
事务管理器，处理ACID属性。

**主要方法：**
- `createTransaction()` - 创建事务
- `commit()` - 提交事务
- `rollback()` - 回滚事务

## 数据存储格式

数据以文件形式存储在指定目录中，每个表对应一个`.db`文件。

## 性能特性

- **B树索引** - O(log n)的查询时间复杂度
- **快速插入** - O(1)的平均插入时间
- **高效更新** - 支持条件更新
- **事务隔离** - 多事务并发处理

## 限制和注意事项

1. 当前实现支持基本的SQL语句，不支持JOIN操作
2. 索引使用哈希实现，可扩展为B树
3. 事务实现支持基本的提交和回滚
4. 条件查询支持基本的比较操作（=, !=, <, >, <=, >=）

## 许可证

MIT License

## 作者

xuyanchi

## 贡献

欢迎提交Issue和Pull Request！

## 联系方式

如有问题或建议，请在GitHub上提交Issue。
