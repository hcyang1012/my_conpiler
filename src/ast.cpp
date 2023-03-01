#include <glog/logging.h>

#include <include/ast.hpp>
#include <memory>
#include <set>
#include <string>

namespace my_compiler {
Ast::Ast(const Type& type) : type_(type) {}
AstCompound::AstCompound() : Ast(Type::AST_COMPOUND) {}
void AstCompound::AddChildren(const std::shared_ptr<Ast> child) {
  children_.push_back(child);
}
std::shared_ptr<AstCompound> AstCompound::Build() {
  return std::make_shared<AstCompound>();
}
std::string AstCompound::GetTypeName() const { return "Compound"; }
const std::set<std::string>& AstCompound::GetDataType() const {
  return data_type_;
}
void AstCompound::AppendDataType(const std::string& data_type) {
  LOG_IF(FATAL, data_type_.find(data_type) != data_type_.end())
      << data_type << " already exists.";
}

AstAssignment::AstAssignment(const std::string& name,
                             std::shared_ptr<Ast> value)
    : Ast(Type::AST_ASSIGNMENT), name_(name), value_(value) {}
std::string AstAssignment::GetTypeName() const { return "Assignment"; }
std::shared_ptr<AstAssignment> AstAssignment::Build(
    const std::string& name, std::shared_ptr<Ast> value) {
  return std::make_shared<AstAssignment>(name, value);
}

const std::string& AstAssignment::GetName() const { return name_; }
std::shared_ptr<Ast> AstAssignment::GetValue() const { return value_; }

AstVariable::AstVariable(const std::string& value)
    : Ast(Type::AST_VARIABLE), value_(value) {}
std::shared_ptr<AstVariable> AstVariable::Build(const std::string& value) {
  return std::make_shared<AstVariable>(value);
}
std::string AstVariable::GetTypeName() const { return "Variable"; }
const std::string& AstVariable::GetValue() const { return value_; }

const std::set<std::string>& AstVariable::GetDataType() const {
  return data_type_;
}
void AstVariable::AppendDataType(const std::string& data_type) {
  LOG_IF(FATAL, data_type_.find(data_type) != data_type_.end())
      << data_type << " already exists.";
}

AstNoop::AstNoop() : Ast(Type::AST_NOOP) {}
std::shared_ptr<AstNoop> AstNoop::Build() {
  return std::make_shared<AstNoop>();
}
std::string AstNoop::GetTypeName() const { return "Noop"; }

AstFunction::AstFunction(std::shared_ptr<AstCompound> value)
    : Ast(Type::AST_FUNCTION), value_(value) {}
std::string AstFunction::GetTypeName() const { return "Function"; }
std::shared_ptr<AstFunction> AstFunction::Build(
    std::shared_ptr<AstCompound> value) {
  return std::make_shared<AstFunction>(value);
}
std::shared_ptr<AstCompound> AstFunction::GetValue() { return value_; }

AstCall::AstCall() : Ast(Type::AST_CALL) {}
std::string AstCall::GetTypeName() const { return "Call"; }
std::shared_ptr<AstCall> AstCall::Build() {
  return std::make_shared<AstCall>();
}
void AstCall::AddChildren(const std::shared_ptr<Ast> child) {
  children_.push_back(child);
}

AstInt::AstInt(int value) : Ast(AST_INT) {}
std::string AstInt::GetTypeName() const { return "Int"; }
std::shared_ptr<AstInt> AstInt::Build(int value) {
  return std::make_shared<AstInt>(value);
}
int AstInt::GetValue() { return value_; }
}  // namespace my_compiler