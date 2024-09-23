#ifndef TASK1_TASK1_RANDOMGENERATOR_HPP
#define TASK1_TASK1_RANDOMGENERATOR_HPP

#include <algorithm>
#include <array>
#include <random>
#include <string>

namespace task1
{

  // the code sucks:
  // 1. It's is not thread-safe,
  //   - thus std::generate cannot be used with a parallel policy
  //   - don't use simultaniously one such object, use multiple objects.
  // 2. It uses mersenne-twister RNG. It's ok, but not the best:
  //  a. not the fastest
  //  b. not the safest. Don't use for password generation.
  // before refactor random generating ( if you need ), at least watch this talk:
  // https://www.youtube.com/watch?v=rCuMjENEa4Q
  // 3. the code uses std::basic_string<...> which is not from ICU, therefore no Unicode support.
  //    - FYI chars in QString are 16bits, therefore it doesn't support Unicode as well as ICU,
  //    therefore Qt for this case wouldn't be the best option ( same as std::basic_string<>)
  //   If this code needs Unicode support, either use ICU or Boost.Locale compiled with ICU.
  // before adding unicode support, check at least this:
  // https://gzuliani.github.io/unicode/files/unicode/unicode-cpp.pdf
  //
  // there's no unicode support, because there's nothing about it in task.
  class RandomGenerator
  {
  public:
    using allocator_type = std::pmr::polymorphic_allocator<char>;

  private:
    std::pmr::string charset_pri;
    std::random_device random_pri{};
    std::mt19937 generator_pri{random_pri()};
    std::uniform_int_distribution<std::size_t> distrib_pri;

  public:
    RandomGenerator(const RandomGenerator &) = delete;
    RandomGenerator(RandomGenerator &&) = delete;
    RandomGenerator &operator=(const RandomGenerator &) = delete;
    RandomGenerator &operator=(RandomGenerator &&) = delete;
    ~RandomGenerator() = default;
    explicit RandomGenerator(std::pmr::string charset, allocator_type alloc = {})
        : charset_pri(std::move(charset), alloc), distrib_pri(0, charset_pri.length() - 1)
    {
    }

    template <std::size_t N, typename Char_T>
    [[nodiscard]] constexpr inline std::array<Char_T, N> generate()
    {
      std::array<Char_T, N> rnd_str;
      std::generate(rnd_str.begin(), rnd_str.end(),
                    [this]() { return charset_pri[distrib_pri(generator_pri)]; });
      return rnd_str;
    }

    [[nodiscard]] inline std::string generate(size_t length)
    {
      std::string rnd_str;
      rnd_str.resize(length);

      std::generate(rnd_str.begin(), rnd_str.end(),
                    [this]() { return charset_pri[distrib_pri(generator_pri)]; });

      return rnd_str;
    }
  };

}  // namespace task1

#endif /* TASK1_TASK1_RANDOMGENERATOR_HPP */
