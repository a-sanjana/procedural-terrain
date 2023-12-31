# pragma once
# include <cstdint>
# include <numeric>
# include <algorithm>
# include <random>

namespace siv
{
	/**
	 * @class PerlinNoise
	 * @brief Class for generating Perlin noise in one, two, or three dimensions.
	 *
	 * This class provides methods for generating Perlin noise in one, two, or three dimensions.
	 */
	class PerlinNoise
	{
	private:

		std::int32_t p[512]; ///< Permutation table.

		/**
		 * @brief Applies the fade function to the input.
		 *
		 * @param t Input value.
		 * @return Faded value.
		 */
		double fade(double t) const noexcept
		{
			return t * t * t * (t * (t * 6 - 15) + 10);
		}

		/**
		 * @brief Performs linear interpolation between two values.
		 *
		 * @param t Interpolation factor.
		 * @param a First value.
		 * @param b Second value.
		 * @return Interpolated value.
		 */
		double lerp(double t, double a, double b) const noexcept
		{
			return a + t * (b - a);
		}

		/**
		 * @brief Calculates the gradient value based on the hash value.
		 *
		 * @param hash Hash value.
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @param z Z-coordinate.
		 * @return Gradient value.
		 */
		double grad(std::int32_t hash, double x, double y, double z) const noexcept
		{
			const std::int32_t h = hash & 15;
			const double u = h < 8 ? x : y;
			const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

	public:

		/**
		 * @brief Constructs a PerlinNoise object with an optional seed.
		 *
		 * @param seed Seed value for randomization. Defaults to the default seed of std::default_random_engine.
		 */
		explicit PerlinNoise(std::uint32_t seed = std::default_random_engine::default_seed)
		{
			reseed(seed);
		}

		/**
		 * @brief Reseeds the PerlinNoise object with a new seed.
		 *
		 * @param seed New seed value.
		 */
		void reseed(std::uint32_t seed)
		{
			for (std::int32_t i = 0; i < 256; ++i)
			{
				p[i] = i;
			}

			std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

			for (size_t i = 0; i < 256; ++i)
			{
				p[256 + i] = p[i];
			}
		}

		/**
		 * @brief Generates octave Perlin noise in one dimension.
		 *
		 * @param x X-coordinate.
		 * @param octaves Number of octaves.
		 * @return Octave Perlin noise value.
		 */
		double noise(double x) const
		{
			return noise(x, 0.0, 0.0);
		}

		/**
		 * @brief Generates Perlin noise in two dimensions.
		 *
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @return Perlin noise value.
		 */
		double noise(double x, double y) const
		{
			return noise(x, y, 0.0);
		}

		/**
		 * @brief Generates Perlin noise in three dimensions.
		 *
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @param z Z-coordinate.
		 * @return Perlin noise value.
		 */
		double noise(double x, double y, double z) const
		{
			const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
			const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
			const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

			x -= std::floor(x);
			y -= std::floor(y);
			z -= std::floor(z);

			const double u = fade(x);
			const double v = fade(y);
			const double w = fade(z);

			const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
			const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

			return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
				grad(p[BA], x - 1, y, z)),
				lerp(u, grad(p[AB], x, y - 1, z),
				grad(p[BB], x - 1, y - 1, z))),
				lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
				grad(p[BA + 1], x - 1, y, z - 1)),
				lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
				grad(p[BB + 1], x - 1, y - 1, z - 1))));
		}

		/**
		 * @brief Generates octave Perlin noise in one dimension.
		 *
		 * @param x X-coordinate.
		 * @param octaves Number of octaves.
		 * @return Octave Perlin noise value.
		 */
		double octaveNoise(double x, std::int32_t octaves) const
		{
			double result = 0.0;
			double amp = 1.0;

			for (std::int32_t i = 0; i < octaves; ++i)
			{
				result += noise(x) * amp;
				x *= 2.0;
				amp *= 0.5;
			}

			return result;
		}

		double octaveNoise(double x, double y, std::int32_t octaves) const
		{
			double result = 0.0;
			double amp = 1.0;

			for (std::int32_t i = 0; i < octaves; ++i)
			{
				result += noise(x, y) * amp;
				x *= 2.0;
				y *= 2.0;
				amp *= 0.5;
			}

			return result;
		}

		double octaveNoise(double x, double y, double z, std::int32_t octaves) const
		{
			double result = 0.0;
			double amp = 1.0;

			for (std::int32_t i = 0; i < octaves; ++i)
			{
				result += noise(x, y, z) * amp;
				x *= 2.0;
				y *= 2.0;
				z *= 2.0;
				amp *= 0.5;
			}

			return result;
		}

		/**
		 * @brief Generates Perlin noise in one dimension and maps it to the range [0, 1].
		 *
		 * @param x X-coordinate.
		 * @return Perlin noise value in the range [0, 1].
		 */
		double noise0_1(double x) const
		{
			return noise(x) * 0.5 + 0.5;
		}

		double noise0_1(double x, double y) const
		{
			return noise(x, y) * 0.5 + 0.5;
		}

		double noise0_1(double x, double y, double z) const
		{
			return noise(x, y, z) * 0.5 + 0.5;
		}

		/**
		 * @brief Generates octave Perlin noise in one dimension and maps it to the range [0, 1].
		 *
		 * @param x X-coordinate.
		 * @param octaves Number of octaves.
		 * @return Octave Perlin noise value in the range [0, 1].
		 */
		double octaveNoise0_1(double x, std::int32_t octaves) const
		{
			return octaveNoise(x, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(double x, double y, std::int32_t octaves) const
		{
			return octaveNoise(x, y, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(double x, double y, double z, std::int32_t octaves) const
		{
			return octaveNoise(x, y, z, octaves) * 0.5 + 0.5;
		}
	};
}
