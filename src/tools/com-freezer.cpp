/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2009
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      CoMFreezer.cpp
 * Project:   SOT
 * Author:    Pierre Gergondet
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <sot-core/com-freezer.h>
#include <sot-core/debug.h>
#include <dynamic-graph/factory.h>


using namespace dynamicgraph;
using namespace sot;

DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(CoMFreezer, "CoMFreezer");

CoMFreezer::CoMFreezer(const std::string & name)
  : Entity(name)
  , m_lastCoM(3)
  , m_previousPGInProcess(false)
  , m_lastStopTime(-1)

  , CoMRefSIN(NULL, "CoMFreezer("+name+")::input(vector)::CoMRef")
  , PGInProcessSIN(NULL, "CoMFreezer("+name+")::input(bool)::PGInProcess")
  , freezedCoMSOUT(boost::bind(&CoMFreezer::computeFreezedCoM, this, _1, _2),
      CoMRefSIN << PGInProcessSIN,
      "CoMFreezer("+name+")::output(vector)::freezedCoM")
{
  sotDEBUGIN(5);

  signalRegistration( CoMRefSIN << PGInProcessSIN << freezedCoMSOUT );

  sotDEBUGOUT(5);
}

CoMFreezer::~CoMFreezer(void)
{
  sotDEBUGIN(5);
  sotDEBUGOUT(5);
  return;
}

ml::Vector & CoMFreezer::computeFreezedCoM(ml::Vector & freezedCoM, const int & time)
{
  sotDEBUGIN(15);

  unsigned PGInProcess = PGInProcessSIN(time); 
  if(PGInProcess) /* CoM unfreezed */
  {
    m_lastCoM = CoMRefSIN(time);
    m_previousPGInProcess = PGInProcess;
  }
  else
  {
    if(m_previousPGInProcess) /* pg.inprocess switch from 1 to 0 */
    {
      m_lastStopTime = time;
      m_lastCoM = CoMRefSIN(time);
      m_previousPGInProcess = PGInProcess;
    }
    else if(time < m_lastStopTime + 200) /* keep updating for 1s */
    {
      m_lastCoM = CoMRefSIN(time);
    }
  }

  freezedCoM = m_lastCoM;

  sotDEBUGOUT(15);

  if(m_lastStopTime < 0)
  {
    m_lastCoM = CoMRefSIN(time);
    m_lastStopTime = time;
    freezedCoM = m_lastCoM;
    return freezedCoM;
  }


  return m_lastCoM;
}

void CoMFreezer::display(std::ostream & os) const
{
  os << "CoMFreezer " << getName() << "." << std::endl;
}
