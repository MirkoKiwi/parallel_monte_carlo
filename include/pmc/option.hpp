#ifndef PMC_OPTION_HPP
#define PMC_OPTION_HPP


#include "pmc/platform.hpp"

namespace pmc {

enum class OptionType { Call, Put };    // Buy, Sell

struct OptionSpec {
    OptionType type{OptionType::Call};
    double spot{};      // S_0 > 0
    double strike{};    // K > 0
    double rate{};      // r
    double vol{};       // sigma > 0
    double expiry{};    // T > 0 [Years]
};


class EuropeanOption {

public:
    explicit EuropeanOption(const OptionSpec &spec);

    [[nodiscard]] const OptionSpec &spec()   const noexcept { return spec_; }
    [[nodiscard]] OptionType        type()   const noexcept { return spec_.type; }
    [[nodiscard]] double            spot()   const noexcept { return spec_.spot; }
    [[nodiscard]] double            strike() const noexcept { return spec_.strike; }
    [[nodiscard]] double            rate()   const noexcept { return spec_.rate; }
    [[nodiscard]] double            vol()    const noexcept { return spec_.vol; }
    [[nodiscard]] double            expiry() const noexcept { return spec_.expiry; }

    [[nodiscard]] EuropeanOption    with_spot(double spot)     const;
    [[nodiscard]] EuropeanOption    with_vol(double vol)       const;
    [[nodiscard]] EuropeanOption    with_type(OptionType type) const;


private:
    OptionSpec spec_;
};



template <OptionType Type>
[[nodiscard]] PMC_HD constexpr double payoff_t(double terminal_spot, double strike) noexcept {
    if constexpr ( Type == OptionType::Call ) {
        return (terminal_spot > strike) ? terminal_spot - strike : 0.0;
    }
    else {
        return (strike > terminal_spot) ? strike - terminal_spot : 0.0;
    }
}

[[nodiscard]] PMC_HD constexpr double payoff(OptionType type, double terminal_spot, double strike) noexcept {
    return (type == OptionType::Call)
               ? payoff_t<OptionType::Call>(terminal_spot, strike)
               : payoff_t<OptionType::Put>(terminal_spot, strike);
}

}   // namespace pmc



#endif  // PMC_OPTION_HPP