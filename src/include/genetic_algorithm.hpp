#ifndef UCTP_GENETIC_ALGORITHM_HPP
#define UCTP_GENETIC_ALGORITHM_HPP

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#define POPULATION_SIZE_CONST 960;
#define ITERATIONS_NUMBER 16;

namespace alg {
int getRandomNumber(int min, int max);

struct Block {
  int blockId;
  int group;
  int subject;
  int subjectType;
  int teacher;

  Block(int b, int g, int s, int st, int t)
      : blockId(b), group(g), subject(s), subjectType(st), teacher(t) {}
};

class Gen {
  int Value;

 public:
  explicit Gen(const int val = 0);

  // Gen(const Gen &g);

  const int &GetValue() const;

  void SetValue(const int &val);
};

class ChromosomeTime {
  std::vector<Gen> TimeChromosome;

 public:
  explicit ChromosomeTime() = default;

  void CopyParts(const std::vector<Gen> &firstPart,
                 const std::vector<Gen> &secondPart, int part);

  void Initialize(const std::vector<Block> &blocks,
                  const std::vector<int> &AllTimes);

  const std::vector<Gen> &GetTimeGenes();

  void NewMutationTime(int i, const std::vector<int> &AllTimes);
};

class ChromosomeAuditory {
  std::vector<Gen> AuditoryChromosome;

 public:
  explicit ChromosomeAuditory() = default;

  void CopyParts(const std::vector<Gen> &firstPart,
                 const std::vector<Gen> &secondPart, int part);

  void Initialize(const std::vector<Block> &blocks,
                  const std::vector<int> &AuditoryType1,
                  const std::vector<int> &AuditoryType2);

  const std::vector<Gen> &GetAuditoryGenes();

  void NewMutationAuditory(int i, const std::vector<Block> &blocks,
                           const std::vector<int> &AuditoryType1,
                           const std::vector<int> &AuditoryType2);
};

class Individual {
  std::shared_ptr<ChromosomeAuditory> ChromAud;
  std::shared_ptr<ChromosomeTime> ChromTime;

 public:
  explicit Individual();

  void Crossing(const std::shared_ptr<Individual> &Ind1,
                const std::shared_ptr<Individual> &Ind2,
                const std::vector<Block> &blocks);

  void Mutate(const std::vector<Block> &blocks,
              const std::vector<int> &AuditoryType1,
              const std::vector<int> &AuditoryType2,
              const std::vector<int> &AllTimes);

  void Initialize(const std::vector<Block> &blocks,
                  const std::vector<int> &AuditoryType1,
                  const std::vector<int> &AuditoryType2,
                  const std::vector<int> &AllTimes);

  void CreateNewChromosomeTime(const std::vector<Block> &blocks,
                               const std::vector<int> &AllTimes);

  void CreateNewChromosomeAuditory(const std::vector<Block> &blocks,
                                   const std::vector<int> &AuditoryType1,
                                   const std::vector<int> &AuditoryType2);

  std::shared_ptr<ChromosomeAuditory> GetAuditoryChromosome();

  std::shared_ptr<ChromosomeTime> GetTimeChromosome();
};

class Population {
  std::vector<Block> blocks;
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  std::vector<int> AllTimes;

  std::vector<std::shared_ptr<Individual>> Individuals;
  int sizeIndividuals;

 public:
  explicit Population();

  explicit Population(const std::vector<Block> &blcks,
                      const std::vector<int> &AudType1,
                      const std::vector<int> &AudType2,
                      const std::vector<int> &AllTmes);

  void InitializeInds(int population);

  std::shared_ptr<Individual> Iterations(int population, int iterations);

  void NewPopulation();

  void Crossingover();

  void Mutation();

  std::shared_ptr<Individual> SearchBest();

  std::vector<std::shared_ptr<Individual>> GetPopulation();
};

class IRule {
 public:
  virtual ~IRule() = default;

  virtual void ForWordMutation(std::shared_ptr<Individual> &Ind,
                               const std::vector<Block> &blocks,
                               const std::vector<int> &AllTimes) = 0;

  virtual int CalcRule(std::shared_ptr<Individual> &Ind,
                       const std::vector<Block> &blocks) = 0;

  virtual void RandomMutation(std::shared_ptr<Individual> &Ind,
                              const std::vector<Block> &blocks,
                              const std::vector<int> &AuditoryType1,
                              const std::vector<int> &AuditoryType2,
                              const std::vector<int> &AllTimes) = 0;
};

class SameAudSameTime : public IRule {
  int R;

 public:
  explicit SameAudSameTime();

  void ForWordMutation(std::shared_ptr<Individual> &Ind,
                       const std::vector<Block> &blocks,
                       const std::vector<int> &AllTimes) override;

  int CalcRule(std::shared_ptr<Individual> &Ind,
               const std::vector<Block> &blocks) override;

  void RandomMutation(std::shared_ptr<Individual> &Ind,
                      const std::vector<Block> &blocks,
                      const std::vector<int> &AuditoryType1,
                      const std::vector<int> &AuditoryType2,
                      const std::vector<int> &AllTimes) override;

  void SetR(const std::vector<Block> &blocks);

  int GetR() const;
};

class SameGroupMoreBlock : public IRule {
  int R;

 public:
  explicit SameGroupMoreBlock();

  void ForWordMutation(std::shared_ptr<Individual> &Ind,
                       const std::vector<Block> &blocks,
                       const std::vector<int> &AllTimes) override;

  int CalcRule(std::shared_ptr<Individual> &Ind,
               const std::vector<Block> &blocks) override;

  void RandomMutation(std::shared_ptr<Individual> &Ind,
                      const std::vector<Block> &blocks,
                      const std::vector<int> &AuditoryType1,
                      const std::vector<int> &AuditoryType2,
                      const std::vector<int> &AllTimes) override;

  void SetR(const std::vector<Block> &blocks);

  int GetR() const;
};

class SameLecMoreBlock : public IRule {
  int R;

 public:
  explicit SameLecMoreBlock();

  void ForWordMutation(std::shared_ptr<Individual> &Ind,
                       const std::vector<Block> &blocks,
                       const std::vector<int> &AllTimes) override;

  int CalcRule(std::shared_ptr<Individual> &Ind,
               const std::vector<Block> &blocks) override;

  void RandomMutation(std::shared_ptr<Individual> &Ind,
                      const std::vector<Block> &blocks,
                      const std::vector<int> &AuditoryType1,
                      const std::vector<int> &AuditoryType2,
                      const std::vector<int> &AllTimes) override;

  void SetR(const std::vector<Block> &blocks);

  int GetR() const;
};

class AllRules {
  std::vector<std::shared_ptr<IRule>> Rules;
  std::vector<int> Penalty;

 public:
  void SetRules();

  int calcFitness(std::shared_ptr<Individual> &Ind,
                  const std::vector<Block> &blocks);

  void SetPenalty(int cnt);

  std::vector<int> &GetPenaltyList();

  void ForWordMutation(std::shared_ptr<Individual> &Ind,
                       const std::vector<Block> &blocks,
                       const std::vector<int> &AllTimes);

  void RandomMutation(std::shared_ptr<Individual> &Ind,
                      const std::vector<Block> &blocks,
                      const std::vector<int> &AuditoryType1,
                      const std::vector<int> &AuditoryType2,
                      const std::vector<int> &AllTimes);
};
}  // namespace alg

#endif  // UCTP_GENETIC_ALGORITHM_HPP
