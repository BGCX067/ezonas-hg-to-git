typedef enum {lure, gren, cut, amo, weap, item, tool}                  item_t;
typedef enum {has_at, has_lz, has_la, has_cm, has_cn, has_sc}    weap_conf;

typedef enum
{
     klobr, lark,
     mp49r, k97, fl71,
     psg9,
     railrif, flakspr, fpgun,
     ezgun, snaket
}
mweap;
typedef enum {light_gr, tron_gr, wave_gr, wind_gr}               tactic_t;
typedef enum {rocket, missl, fire_gr, mqrk_gr, smtex_gr}         bomb_t;
typedef enum {ripclaw, blade, kitemchen}                         closearm_t;
typedef enum {stdb, hvel, srg, fl, stackcap, combcap, flak}      amun_t;
typedef enum {serum, pill}                                       consm_t;
typedef enum {breath, lightbender, spyborg, eyz}                 item_t;
typedef enum {lighter, lamp, zpda, pen, smokes, scopesight}      tool_t;

// magnetic grenade; magnetically push
// all grenade have a magnet mode, or can be slotted in a ball.

class game_item
{
     game_item(int it)
     {
          switch(it)
          {
               case lure:     
               case gren:
               case cut:
               case amo:
               case weap:
               case item:
               case tool:
          }
     
     
     }


}



// some kinds of sky walker fighting cyborgs. 't's gonna be so lol.
#define LAUNCH_HEIGHT = 1; // meter
#define pn(s) printf("%s/n", s)
#define ps(s) printf("%s", s)
#define pl(s) printf("\n%s\n", s)
typedef struct { int id, state; };
typedef struct { int item, state; }
  //itemids :

  wind_gr,
  // as if puppy poopy lets go a big fart. played team fortress, called it conc grenade

  fire_gr,
  // napalm like. "thermite" is written in red

  light_gr, 
  // blackens screen for 3s, reveals invis in a 25m radius. Seems to create some sort of
  // matter-safe blackhole after it explodes if I close my eyes.

  tron_gr,
  //jam radar, electronic system and spyborgs.

  quark_gr,
  // wow. this made a very bright flash

  wave_gr,
  // I hate this one: this creates a very noisy wave that brokes all structures around
  // sometimes it ever crack plexiglas and some heavy metals ideal to break those nasty armored doors
  
  // ********** WEAPONS **********
  // these two next weapons can be heard in a large radius, so be careful
  //those last both can be modified later to be added

  pistol,
  // some standard semi automatic gun; can use high velocity munitions

  gunarm,
  //2 hand never saw this model, but it fucking rocks jesus

  ezgun,
  // electric gun: send a very few photons, shock the enemy without killing it. silent (5m)

  fgun,
  // a quite heavy gun that creates a cone-like magnetic force field, that repulse every metal
  // can be upgraded to bend more material, so that not only metal can be repulsed, but other heavy matter
  // like water

  spyborg,
  //invis fly-sized cyborg: can listen and watch upto a 10m radius. very low speed.
  // on the remote, there is a autodestruct button
  //some spyborg can fly
  //viewed in 3rd person

  blade,
  // plasma 1 feet long. remembers me some funny movies about wars and stars. Was a funny movie though.
  // the main character look gay

  claw,
  // steel classic blade. a blade I can punch with to be somewhat more... unkind
  
  serum,
  // 1min knock out. useful to make a moron shut up for a while
  
  pill,
  //instant aim, 25% speed boost, 100% aiming speed boost, close combat is doubled

  suit,
  //5s invis, 5 charges, max two consecutives, only once (press 2 times)
  //cant invis after an invis ends, for 25s
  // never saw or heard about this technology! but this kick ass!
  //always wanted to be a ninja like ask-a-ninja !
  // I don't really know how this works, it's just a wired bikini-kind robe...
  // those scientist are mad genius, it's scary some times.
  
  rocket,
  // 10m/s or 15 (depending) quite dangerous stuff. hope CIA knows about this...
  // it is written "warning: semtex" on it. Already saw it explode: my ears are still in pain.
  // it is very small and easy to use, and it blast quite heavily
  
  cat,
  // send a cat or rat that escape from char (don't laugh plz). Sorry fella, I really need your help.
  // the game master is quite crazy, but I need to save the world apparently. Mark say I can revive you!

  breathkit,
  // some technology inspired from fishes. will tell my girl friend I have one and get another one,
  // we'll go naughty in the swimming pool! :)
  
  //status:
  // 0: normal
  // 1: destroyed
  // 2: repearable
  // 3: invis
  // 4: sleep
  // 5: dead // disappear after 30s
  // 6: knock (usually 10s)
  // 7: slewn, eg broken feet/leg (eg robots)
  // 8: sunk (10s max surviving after stopped moving for a period greater than 25s)
  // 9: flying

  cam_efo,
  //this cam will try to display the scene, items, characters
  cam_omni,
  // a cam used for dream and ethereal/debug scening
  cam_ego
  // pure 1st person camera, strictly stuck to the characters head.
  //useful for telekinesy or mond r eading
;

void item_mgr(int item_id)
{
  switch()
    {
    case 0: nothing();            break; //fist //remember to make a shao lin styled pos
    case 1: destroy(item_id);     break; //bybye
    case 2: break_it(item_id);    break; //mummy! he broke my m4 !
    case 3: hide(item_id);        break; //invis
    case 4: sing_a_song(item_id); break; //make it sleep
    case 5: kill_it(item_id);     break; //make it ...dead.
    case 6: hit(item_id);         break; //FUCKING ITEM
    case 7: karate(item_id);      break; //battle dance managing
    case 8: flush(item_id);       break; //pour some water on it

    }
}


void launch(int dist, float &prbol[256]) // 256 points traj is quite a lot
// click right will be used
{
  float base_height = LAUNCH_HEIGHT;
  for (int = -256; i < 255; ++i)
    {
      float j = ((float)i)/256;
      traj_parabolic[i] = (base_height - j) * (base_height - j);
      // this will hope fully creat a parabolic line
    }
}

