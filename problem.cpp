/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "problem.h"
#include <iostream>
#include <math.h>

namespace ems
{
  namespace Scavenger
  {
    Problem::Problem(ai::Search::State *initial_state_in, Model  *world_in)
      : ai::Search::Problem(initial_state_in),
        world(world_in),
        goal_state(0)
    {
      /* empty */
    }
    Problem::~Problem()
    {
      if(this->world)
        {
          delete this->world;
          this->world = 0;
        }
      if(this->goal_state)
        {
          delete this->goal_state;
          this->goal_state = 0;
        }
    }

    std::vector<ai::Search::Action *> Problem::Actions(const ai::Search::State * const state_in)
    {
      std::vector<ai::Search::Action *> actions;
          const State * const state = dynamic_cast<const State * const>(state_in);
          std::pair<double, double> pair;
          bool noquit;
          pair.first = state->GetX();
          pair.second = state->GetY();
//          if(it == mCells.end() || state->GetCharge() < 1.0
          if(state->GetCharge() < 0.0)
          {
              //std::cout << "the key didnt exist: " << pair.first << " , " << pair.second << std::flush << std::endl;
              return actions;
          }
          Cell * mCell = mCells[pair];
//         std::cout << "cell number is: " << mCell->mcell_num << ".  state cell: " << state->GetCellNum() << std::flush << std::endl;
//          std::cout << "the key is: " << pair.first << " , " << pair.second << std::flush << std::endl;
//          std::cout << "cell nums in actions: " << mCell->mcell_num << " " <<  state->mCell->mcell_num << std::endl;
//          if(mCell->mcell_num == state->mCell->mcell_num)
//          if(fabs(mCell->mcell_x - state->GetX()) < 0.01 && fabs(mCell->mcell_y - state->GetY()) < 0.01)
//            {
                    if ((mCell->msnorth == "plain"|| mCell->msnorth == "mud"/*|| mCell->msnorth == "rocks"*/))
                    {
                        Action * new_action = new Action();
                         new_action->SetType(((int)ai::Scavenger::Action::GO_NORTH));
                         actions.push_back(new_action);
                         noquit = true;
                    }
                    if ((mCell->mseast ==  "plain" || mCell->mseast == "mud" /*|| mCell->mseast == "rocks"*/))
                    {
                        Action * new_action = new Action();
                        new_action->SetType(((int)ai::Scavenger::Action::GO_EAST));
                         actions.push_back(new_action);
                         noquit = true;
                    }
                    if ((mCell->mswest ==  "plain" || mCell->mswest == "mud" /*|| mCell->mswest == "rocks"*/))
                    {
                        Action * new_action = new Action();
                        new_action->SetType(((int)ai::Scavenger::Action::GO_WEST));
                         actions.push_back(new_action);
                         noquit = true;
                    }
                    if ((mCell->mssouth ==  "plain" || mCell->mssouth == "mud" /*|| mCell->mssouth == "rocks"*/))
                    {
                        Action * new_action = new Action();
                       new_action->SetType(((int)ai::Scavenger::Action::GO_SOUTH));
                         actions.push_back(new_action);
                         noquit = true;
                    }
                    if(!noquit)
                    {
                        Action * new_action = new Action();
                        std::cout << "quit action" << std::flush << std::endl;
                        new_action->SetType(((int)ai::Scavenger::Action::QUIT));
                         actions.push_back(new_action);
                    }
//            }
      return actions;
    }
      
    ai::Search::State *Problem::Result(const ai::Search::State * const state_in, const ai::Search::Action * const action_in)
    {
      const State * const state = dynamic_cast<const State * const>(state_in);
      State  * new_state  = new State();
      if(state->GetCharge() < 1.0) return new_state;
      const Action * const action = dynamic_cast<const Action * const>(action_in);
      int dx[4] = { 0, 0, 1000, -1000 };
      int dy[4] = {  1000, -1000, 0, 0 };
      int i = action->GetType();
      int new_x = state->GetX() + dx[i];
      int new_y = state->GetY() + dy[i];
      std::pair<double, double> pair;
      pair.first = new_x;
      pair.second = new_y;
      std::map<std::pair<double, double>, Cell*>::const_iterator it;
      it = this->mCells.find(pair);
      if(it != mCells.end())
      {
          new_state->SetX(new_x);
          new_state->SetY(new_y);
          Cell * cell = mCells[pair];
          new_state->SetCell(*cell);
          new_state->SetZ(cell->mcell_z);
          new_state->SetCellNum(cell->mcell_num);
          new_state->SetCharge(state->GetCharge());
          new_state->SetHP(state->GetHP());
          double step = StepCost(state, action, new_state);
          new_state->SetCharge(new_state->GetCharge()-step);
//          double hpcost = HPCost(state, action, new_state);
//          new_state->SetHP(new_state->GetHP() - hpcost);
//              std::cout << state->GetX() << " what is the old X? " << std::endl;
//              std::cout << state->GetY() << " what is the old Y? "  << std::endl;
//              std::cout << new_state->GetX() << " what is the new X? "  << std::endl;
//              std::cout << new_state->GetY() << " what is the new Y? " << std::endl;
          return new_state;
      }
      new_state->SetX(state->GetX());
      new_state->SetY(state->GetY());
      new_state->SetZ(state->GetZ());
      return new_state;
    }
      
    bool   Problem::GoalTest(const ai::Search::State * const state_in) const
    {
      const State * const state = dynamic_cast<const State * const>(state_in);
      //bool test = (*(this->goal_state) == *state);
      //std::cout << "Goal Test: " <<  test << " " << state->GetX() << " " << state->GetY() << " " << std::flush << std::endl;
      return *(this->goal_state) == *state;
    }
    
    double Problem::StepCost(const ai::Search::State  * const state1_in,const ai::Search::Action * const action_in,const ai::Search::State  * const state2_in) const
    {
      const State  * const state1 = dynamic_cast<const State * const>(state1_in);
      const Action * const action = dynamic_cast<const Action * const>(action_in);
      const State  * const state2 = dynamic_cast<const State * const>(state2_in);
      int i = action->GetType();
      double elevationchange = state2->GetZ() - state1->GetZ(); //new minus original
      double step = 1.0;
      step += elevationchange / 1000.0;
      if ((state1->mCell->msnorth == "mud" && i == 0) || (i == 1 && state1->mCell->mssouth == "mud") || (i == 2 && state1->mCell->mseast == "mud") || (i == 3 && state1->mCell->mswest == "mud"))
      {   
          step += 1.0;
      }
//      if ((state1->mCell->msnorth == "rocks" && i == 0) || (i == 1 && state1->mCell->mssouth == "rocks") || (i == 2 && state1->mCell->mseast == "rocks") || (i == 3 && state1->mCell->mswest == "rocks"))
//      {   
//          step += 1.0;
//      }
      return step;
    }
    double Problem::HPCost(const ai::Search::State  * const state1_in,const ai::Search::Action * const action_in,const ai::Search::State  * const state2_in) const
    {
      const State  * const state1 = dynamic_cast<const State * const>(state1_in);
      const Action * const action = dynamic_cast<const Action * const>(action_in);
      const State  * const state2 = dynamic_cast<const State * const>(state2_in);
      int i = action->GetType();
      double elevationchange = state2->GetZ() - state1->GetZ(); //new minus original
      double step = 0.0;
      step += elevationchange / 1000.0;
      step = 0.0;
      if ((state1->mCell->msnorth == "rocks" && i == 0) || (i == 1 && state1->mCell->mssouth == "rocks") || (i == 2 && state1->mCell->mseast == "rocks") || (i == 3 && state1->mCell->mswest == "rocks"))
      {   
          step += 2.0;
      }
      return step;
    }
    
    double Problem::Heuristic(const ai::Search::State  * const state_in) const
    {
        const State  * const state1 = dynamic_cast<const State * const>(state_in);
        double x = state1->GetX();
	double y = state1->GetY();
       double z = state1->GetZ();
	double gY = world->mgoaly;
	double gX = world->mgoalx;
        double gZ = world->mgoalz;
	double dist = (fabs(gX - x) + fabs(y-gY) + (gZ - z))/1000;
//        std::cout << "heuristic: " << gY << " " << gX << " xyz: " << x << " " << y << " " << z << " " << dist << " = distance " << std::endl;
	return dist;
    }
      
    bool Problem::SetGoal(State *goal_state_in)
    {
      this->goal_state = goal_state_in;
      return true;
    }
  }
}