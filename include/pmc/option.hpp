#ifndef OPTION_HPP
#define OPTION_HPP



#include <algorithm>



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

}



#endif  // OPTION_HPP