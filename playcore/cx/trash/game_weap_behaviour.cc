/*
enum { cannon, laser, lamp, scope, cam, upgrade };
struct weap_spec
{
  int std = 25, srg = 0, hvl = 0, flak = 0, fl = 0, stackcap = 0, combcap = 0;
  bool spec[6] = {true, false, true, true, false, true, false};
};
*/
// default weapon
class game_weap_behav
{
  bool autom, laser, lamp, cam = true;
  bool cannon = false; // this is an extension, like a silencer
  bool scope = false; // has to be equipped on
  virtual void upgrade() {}
  
};

class weap_klobr : public game_weap_behav
{
  autom = false;
  srg = 5;
  void upgrade {autom = true; hvl = 15; cannon = true;}
};

class weap_jeagle : public game_weap_behav
{
  autom = false;
  hvl = 8; srg = 10; std = 0;
  void upgrade {cannon = true;}
};

class weap_mp49r : public game_weap_behav
{
  hvl = 50; std = 0;
  void upgrade {scope = true; cannon = true;}

};

class weap_k97 : public game_weap_behav
{
  std = 30;
  void upgrade {scope = true;}
};

class weap_fl71 : public game_weap_behav
{
  srg = 15; hvl = 25; scope = true; fl = 100; std = 50;
  void upgrade {stackcap = 3; cannon = true;}
};

class weap_psg9 : public game_weap_behav
{
  autom = false; scope = true;
  hvl = 15;  std = 0;
  void upgrade {srg = 10; cannon = true;}
};
// ### special  ###
class weap_railrif : public game_weap_behav
{
  autom = false;
  combcap = 3; std = 0;
};

class weap_flakspr : public game_weap_behav
{
  autom = false;
  flak = 10; std = 0;
};

class weap_ezgun : public game_weap_behav
{
  autom = false;
  fl = 5; std = 0;
};

class weap_fgun : public game_weap_behav
{
  autom = false;
  comcap = 5; laser = false; 
  std = 0;
};

class weap_snaket : public game_weap_behav
{
  autom = false; cannon = true;
  hvl = 8; std = 0;
};
