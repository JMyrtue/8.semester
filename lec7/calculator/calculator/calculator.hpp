#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace calculator
{
    enum class op_t {///< operator sign for assignment/unary/binary expression
        plus,  ///< unary plus, like +v
        minus, ///< unary minus, like -v
        mult, ///< multiplication
        div, ///< division
        assign ///< assignment, like v <<= v
    };

    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;

    /** Forward declarations to get around circular dependencies: */
    struct expr_t;

    /** Class representing a variable */
    class var_t
    {
        size_t id; ///< stores the variable identifier
        explicit var_t(size_t id): id{id} {}
    public:

        double operator()(const state_t& s) const { return s[id]; }
        friend class symbol_table_t;
        friend struct assign_t;
        friend struct expr_t;
    };

    class symbol_table_t
    {
        std::vector<std::string> names; ///< stores the variable names
        std::vector<double> initial;    ///< stores the initial values of variables
    public:
        /// Creates a variable with given name and initial value
        [[nodiscard]] var_t var(std::string name, double init = 0) {
            auto res = names.size();
            names.push_back(std::move(name));
            initial.push_back(init);
            return var_t{res};
        }
        /// Creates a system state initialized with initial variable values
        [[nodiscard]] state_t state() const { return {initial}; }
    };

    /**
     * expr_t represents an expression and implements all operations.
     * TODO: such design does not scale and has to be refactored into distinct AST classes.
     */
    struct term_t {
        term_t() = default;
        virtual ~term_t() = default;
        virtual double operator() (state_t&) const = 0;
    };

    struct const_t : term_t{
    private:
        double value{};
    public:
        double operator()(state_t&) const override { return value; }
    };

    struct assign_t : term_t {
    private:
        std::shared_ptr<var_t> var;
        std::shared_ptr<term_t> term;
        op_t op;
    public:
        assign_t(std::shared_ptr<var_t> var, std::shared_ptr<term_t> term): var{var}, term{term} {}
        double operator()(state_t& s) const override {
            switch (op) {
                case op_t::assign: return s[var->id] = term->operator()(s);
                case op_t::plus: return s[var->id] += term->operator()(s);
                case op_t::minus: return s[var->id] -= term->operator()(s);
                case op_t::mult: return s[var->id *= term->operator()(s)];
                default: throw std::runtime_error("Invalid operation");
            }
        };
    };

    struct unary_t : term_t {
    private:
        std::shared_ptr<term_t> term;
        op_t op;
    public:
        unary_t(std::shared_ptr<term_t> term, op_t op): term{term}, op{op} {}
        double operator()(state_t& s) const override {
            switch (op) {
                case op_t::plus: return (*term)(s);
                case op_t::minus: return -(*term)(s);
                default : throw std::runtime_error("Invalid operation");
            }
        }
    };

    struct binary_t : term_t {
    private:
        std::shared_ptr<term_t> term1;
        std::shared_ptr<term_t> term2;
        op_t op;
    public:
        binary_t(std::shared_ptr<term_t> term1, std::shared_ptr<term_t> term2, op_t op): term1{term1}, term2{term2}, op{op} {}
        double operator()(state_t& s) const override {
            switch (op) {
                case op_t::plus: return (*term1)(s) + (*term2)(s);
                case op_t::minus: return (*term1)(s) - (*term2)(s);
                case op_t::mult: return (*term1)(s) * (*term2)(s);
                case op_t::div: return (*term1)(s) / (*term2)(s);
                default : throw std::runtime_error("Invalid operation");
            }
        }
    };

    struct expr_t
    {
        std::shared_ptr<term_t> term;

        double operator()(state_t& s) const {
            return term->operator()(s);
        }

        expr_t(std::shared_ptr<term_t> term): term{term} {}
    };

    /** unary operators: */
    inline expr_t operator+(const expr_t& e) { return expr_t{std::make_shared<unary_t>(e.term, op_t::plus)}; }
    inline expr_t operator-(const expr_t& e) { return expr_t{std::make_shared<unary_t>(e.term, op_t::minus)}; }

    /** binary operators: */
    inline expr_t operator+(const expr_t& e1, const expr_t& e2) { return expr_t{std::make_shared<binary_t>(e1.term, e2.term, op_t::plus)}; }
    inline expr_t operator-(const expr_t& e1, const expr_t& e2) { return expr_t{std::make_shared<binary_t>(e1.term, e2.term, op_t::minus)}; }
    inline expr_t operator*(const expr_t& e1, const expr_t& e2) { return expr_t{std::make_shared<binary_t>(e1.term, e2.term, op_t::mult)}; }
    inline expr_t operator/(const expr_t& e1, const expr_t& e2) { return expr_t{std::make_shared<binary_t>(e1.term, e2.term, op_t::div)}; }
    inline expr_t operator<<=(const var_t& v, const expr_t& e) { return expr_t{std::make_shared<assign_t>(v, e.term, op_t::assign)}; }
    inline expr_t operator+=(const var_t& v, const expr_t& e) { return expr_t{std::make_shared<assign_t>(v, e.term, op_t::plus)}; }
    inline expr_t operator-=(const var_t& v, const expr_t& e) { return expr_t{std::make_shared<assign_t>(v, e.term, op_t::minus)}; }
    inline expr_t operator*=(const var_t& v, const expr_t& e) { return expr_t{std::make_shared<assign_t>(v, e.term, op_t::mult)}; }

    /// TODO: implement multiplication
    /// TODO: refactor expr_t into AST terms
    /// TODO: add support for constant expressions like: 7
    /// TODO: add support for printing
}

#endif // INCLUDE_ALGEBRA_HPP
