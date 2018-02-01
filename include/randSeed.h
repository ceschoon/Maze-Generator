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
		void init(int seed);

	private:
		int m_seed;
		int m_timesUsed;
		int m_randNums[1024];
};

#endif // RANDSEED_H