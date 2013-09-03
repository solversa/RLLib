/*
 * Environment.h
 *
 *  Created on: Aug 28, 2013
 *      Author: sam
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Vector.h"
#include "Action.h"
#include "Math.h"

using namespace RLLib;

template<class O>
class TRStep
{
  public:
    DenseVector<O>* o_tp1;
    double r_tp1;
    double z_tp1;
    bool endOfEpisode;
    TRStep(const int& nbVars) :
        o_tp1(new DenseVector<O>(nbVars)), r_tp1(0.0f), z_tp1(0.0f), endOfEpisode(false)
    {
    }

    void updateRTStep(const double& r_tp1, const double& z_tp1, const bool& endOfEpisode)
    {
      this->r_tp1 = r_tp1;
      this->z_tp1 = z_tp1;
      this->endOfEpisode = endOfEpisode;
    }

    ~TRStep()
    {
      delete o_tp1;
    }
};

template<class O>
class Environment
{
  public:
    Environment(int nbVars, int nbDiscreteActions, int nbContinuousActions) :
        output(new TRStep<O>(nbVars)), discreteActions(new GeneralActionList(nbDiscreteActions)), continuousActions(
            new GeneralActionList(nbContinuousActions)), itsOn(false)
    {
    }

    virtual ~Environment()
    {
      delete output;
      delete discreteActions;
      delete continuousActions;
    }

  public:
    virtual void initialize() =0;
    virtual void step(const Action& action) =0;

    virtual void draw() const
    {/*To output useful information*/
    }

    virtual void setOn(const bool& itsOn)
    {
      this->itsOn = itsOn;
    }

    virtual bool getOn() const
    {
      return itsOn;
    }

    virtual ActionList& getDiscreteActionList() const
    {
      return *discreteActions;
    }

    virtual ActionList& getContinuousActionList() const
    {
      return *continuousActions;
    }

    virtual const TRStep<O>& getTRStep() const
    {
      return *output;
    }

    virtual const DenseVector<O>& getVars() const
    {
      return *output->o_tp1;
    }

  protected:
    virtual void updateRTStep() =0;
    virtual bool endOfEpisode() const =0;
    virtual float r() const =0;
    virtual float z() const =0;

  protected:
    TRStep<O>* output;
    ActionList* discreteActions;
    ActionList* continuousActions;
    bool itsOn;
};

#endif /* ENVIRONMENT_H_ */