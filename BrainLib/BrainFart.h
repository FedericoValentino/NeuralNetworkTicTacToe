#include <vector>
#include <list>

//TODO Backward Propagation

class BrainFart{
public:
    BrainFart(std::vector<int> layerSizes);

    float* feedForward(std::vector<float> input);

    void backwardPropagation(std::vector<float> input);

    void mutate();

    void freeBrain();

    static BrainFart* reproduce(BrainFart* father, BrainFart* mother);


private:
    float reLU(float x);

    std::vector<int> dimensions;

    float*** layers;

    float*** weights;

    void initializeWeights();
};

