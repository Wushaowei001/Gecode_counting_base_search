//
// Created by sam on 29/04/16.
//

#ifndef CBS_ALLDIFFCBS_H
#define CBS_ALLDIFFCBS_H

#include <complex>
#include "CBSConstraint.hpp"

class AllDiffCBS : public CBSConstraint/*<View, Val>*/ {
public:
    AllDiffCBS(Space &home, const IntVarArgs &x);

    AllDiffCBS(Space &home, bool share, AllDiffCBS &c);

    CBSConstraint *copy(Space &home, bool share, CBSConstraint &c) override;

    CBSPosValDensity getDensity(std::function<bool(double,double)> comparator) override;

    void precomputeDataStruct(int nbVar, int largestDomainSize, int minValue) override;

private:
    /* Factors precomputed for every value in the domain of x. Thoses factors are used to compute the Minc and Brégman
     * upper bound for the permanent. */
    class MincFactors {
    public:
        MincFactors();

        MincFactors(int largestDomainSize);

        MincFactors(const MincFactors &mf);

        double get(int domSize);

    private:
        /* Recursive function for precomputing mincFactors from 1..n */
        double precomputeMincFactors(int n);

    private:
        double *mincFactors;
        int largestDomainSize;
    };

    /* Factors precomputed for every index and domain size in x. Thoses factors are used to compute the Liang and Bai
     * upper bound for the permanent */
    class LiangBaiFactors {
    public:
        LiangBaiFactors();

        LiangBaiFactors(int nbVar, int largestDomainSize);

        LiangBaiFactors(const LiangBaiFactors &lb);

        double get(int index, int domSize);

    private:
        void precomputeLiangBaiFactors();

    private:
        double **liangBaiFactors;
        int nbVar;
        int largestDomainSize;
    };

private:
    static MincFactors mincFactors;
    static LiangBaiFactors liangBaiFactors;
};

#endif //CBS_ALLDIFFCBS_H
