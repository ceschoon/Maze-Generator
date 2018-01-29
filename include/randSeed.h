#ifndef RANDSEED_H
#define RANDSEED_H

class RandSeed
{
	public:
		RandSeed(int seed);
		RandSeed();
		~RandSeed();

		const int getSeed() const {return m_seed;}
		int randomWithSeed();

	private:
		int m_seed;
};

#endif // RANDSEED_H