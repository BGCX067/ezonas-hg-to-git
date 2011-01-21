#define AUTOM     0x1
#define LASER     0x2
#define LAMP      0x3
#define CAM       0x4
#define CANNON    0x5
#define SCOPE     0x6

#define NUMBER_AMMO 7
#define NUMBER_WEAPONS 11

/*
enum { cannon, laser, lamp, scope, cam, upgrade };
struct weap_spec
{
  int std = 25, srg = 0, hvel = 0, flak = 0, fl = 0, stackcap = 0, combcap = 0;
  bool spec[6] = {true, false, true, true, false, true, false};
};
*/
// default weapon
class game_weap
{
public:
  bool autom, laser, lamp, cam, cannon, scope;
  int std, srg, hvel, flak, fl, stackcap, combcap;
  virtual void upgrade () {}
  public:
  void game_weap ()
  {
    std = 25; srg = 0; hvel = 0; flak = 0; fl = 0; stackcap = 0; combcap = 0;
    autom = true; laser = true; lamp = true; cam = true; cannon = false; scope = false;
  }
};

class clip_ammo
{
  int clip [7];
  public:
  clip_ammo () { for (int i = 1; i < NUMBER_AMMO; ++i) clip [i] = 0; }
  int ammo (int ammo_type) {return clip[i];}
}

enum amun       {std, hvel, srg, fl, stackcap, combcap, flak};

class weap_klobr {}; // little pistol, glock like
class weap_jeagle {}; // big pistol, deagle like
class weap_mp49r {}; // front loaded gun rifle, m4 like
class weap_k97 {}; // old rifle (pretty uch an ak)
class weap_fl71 {}; // rear loaded gun, multi ammo, p90 like
class weap_psg9 {}; // read loaded rifle, long range, (guess)

  // ### special  ###
class weap_railrif {}; // rail gun 3 ammo ()
class weap_flakspr {}; // super shotgun
class weap_ezgun {}; // tazer-like gun, with electrons
class weap_fgun {}; // magnetic gun
class weap_snaket {}; // james bond like silenced gun, shrapnel bullets

// conctructors
weap_klobr   :: weap_klobr     () {autom = false; srg = 5;};
weap_jeagle  :: weap_jeagle    () {autom = false; hvel = 8; srg = 10; std = 0;};
weap_mp49r   :: weap_mp49r     () {hvel = 50; std = 0;};
weap_k97     :: weap_k97       () {std = 30;};
weap_fl71    :: weap_fl71      () {srg = 15; hvel = 25; scope = true; fl = 100; std = 50;};
weap_psg9    :: weap_psg9      () {autom = false; scope = true; hvel = 15; std = 0;};

// ### special  ###
weap_railrif :: weap_railrif   () {autom = false; combcap = 3; std = 0;};
weap_flakspr :: weap_flakspr   () {autom = false; flak = 10; std = 0;};
weap_ezgun   :: weap_ezgun     () {autom = false; fl = 5; std = 0;};
weap_fgun    :: weap_fgun      () {autom = false; comcap = 5; laser = false; std = 0;};
weap_snaket  :: weap_snaket    () {autom = false; cannon = true; hvel = 8; std = 0;};

// upgrades
void weap_klobr  :: upgrade    () {autom = true; hvel = 15; cannon = true;}
void weap_jeagle :: upgrade    () {cannon = true;}
void weap_mp49r  :: upgrade    () {scope = true; cannon = true;}
void weap_k97    :: upgrade    () {scope = true;}
void weap_fl71   :: upgrade    () {stackcap = 3; cannon = true;}
void weap_psg9   :: upgrade    () {srg = 5; cannon = true;}


