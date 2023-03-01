#pragma once
#include <include/token.hpp>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace my_compiler {
class Ast {
 public:
  enum Type {
    AST_COMPOUND,
    AST_FUNCTION,
    AST_CALL,
    AST_INT,
    AST_ASSIGNMENT,
    AST_DEFINITION_TYPE,
    AST_VARIABLE,
    AST_STATEMENT,
    AST_NOOP,
  };

  Ast(const Type& type);

  virtual std::string GetTypeName() const = 0;

 private:
  const Type type_;
};

class AstCompound : public Ast {
 public:
  AstCompound();
  std::string GetTypeName() const override;

  static std::shared_ptr<AstCompound> Build();

  void AddChildren(const std::shared_ptr<Ast> child);
  const std::set<std::string>& GetDataType() const;
  void AppendDataType(const std::string& data_type);

 private:
  std::vector<std::shared_ptr<Ast>> children_;
  std::set<std::string> data_type_;
};

class AstAssignment : public Ast {
 public:
  AstAssignment(const std::string& name, std::shared_ptr<Ast> value);
  std::string GetTypeName() const override;
  static std::shared_ptr<AstAssignment> Build(const std::string& name,
                                              std::shared_ptr<Ast> value);

  const std::string& GetName() const;
  std::shared_ptr<Ast> GetValue() const;

 private:
  const std::string name_;
  std::shared_ptr<Ast> value_;
};

class AstVariable : public Ast {
 public:
  AstVariable(const std::string& value);
  std::string GetTypeName() const override;
  const std::string& GetValue() const;
  const std::set<std::string>& GetDataType() const;
  void AppendDataType(const std::string& data_type);

  static std::shared_ptr<AstVariable> Build(const std::string& value);

 private:
  const std::string value_;
  std::set<std::string> data_type_;
};

class AstNoop : public Ast {
 public:
  AstNoop();
  std::string GetTypeName() const override;
  static std::shared_ptr<AstNoop> Build();
};

class AstFunction : public Ast {
 public:
  AstFunction(std::shared_ptr<AstCompound> value);
  std::string GetTypeName() const override;
  static std::shared_ptr<AstFunction> Build(std::shared_ptr<AstCompound> value);
  std::shared_ptr<AstCompound> GetValue();

 private:
  std::shared_ptr<AstCompound> value_;
};

class AstCall : public Ast {
 public:
  AstCall();
  std::string GetTypeName() const override;
  static std::shared_ptr<AstCall> Build();

  void AddChildren(const std::shared_ptr<Ast> child);

 private:
  std::vector<std::shared_ptr<Ast>> children_;
};

class AstInt : public Ast {
 public:
  AstInt(int value);
  std::string GetTypeName() const override;
  static std::shared_ptr<AstInt> Build(int value);
  int GetValue();

 private:
  int value_;
};

}  // namespace my_compiler