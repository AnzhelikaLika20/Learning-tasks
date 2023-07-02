#include "word2vec.h"

#include <math.h>

#include <vector>

double Cos(std::vector<int> vect1, std::vector<int> vect2) {
    double scal = 0;
    for (size_t i = 0; i < vect1.size(); ++i) {
        scal += vect1[i] * vect2[i];
    }
    double sum_of_sqrts1 = 0;
    double sum_of_sqrts2 = 0;
    for (size_t i = 0; i < vect1.size(); ++i) {
        sum_of_sqrts1 += vect1[i] * vect1[i];
        sum_of_sqrts2 += vect2[i] * vect2[i];
    }
    double mod1 = sqrt(sum_of_sqrts1);
    double mod2 = sqrt(sum_of_sqrts2);
    return scal / (mod1 * mod2);
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> list_of_words;
    if (words.size() < 2) {
        return list_of_words;
    }
    list_of_words.push_back(words[1]);
    double sample = Cos(vectors[0], vectors[1]);
    for (size_t i = 2; i < words.size(); ++i) {
        double cos = Cos(vectors[0], vectors[i]);
        if (cos > sample) {
            sample = cos;
            list_of_words.clear();
            list_of_words.push_back(words[i]);
        } else if (cos == sample) {
            list_of_words.push_back(words[i]);
        }
    }
    return list_of_words;
}
