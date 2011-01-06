enum mweap
  {
    klobr,
    jeagle,

    mpr49r,
    k97,
    fl71,

    psg9,

    railrif,
    flakspr,

    ezgun,
    fgun,
    snaket // poison gun, fatal and silent. can load hvel
  };

enum amun
  {
    std,
    hvel, // semtex
    srg,
    combcap,
    flak,
    fl,
    stackcap
  };

enum consm
  {
    serum,
    pill
    //pressure pill
  };

enum kit
  {
    breath,
    lightbender,
    spyborg
  };

enum closearm
  {
    ripclaw,
    blade,
    kitchen
  };

enum tactic
  {
    rocket,
    missl,
    fire_gr,
    light_gr,
    tron_gr,
    wave_gr,
    mqrk_gr, // magnetic grenade; magnetically push
    wind_gr,
    // all grenade have a magnet mode, or can be slotted in a ball.
    smtex_gr
    //big badaboum
  };
enum {hand, gun, amo, item, kit, gren};

#include <string.h>

class item_descr
{
  string descript[8][32];

  //
  descript[hand][] = "";

  //
  descript[gun][klobr] =
    "some standard semi automatic gun; can use high velocity munitions";
  descript[gun][jeagle] =
    "";
  
  //
  descript[amo][] = "";
  descript[amo][] = "";
  descript[amo][] = "";
  descript[amo][] = "";
  descript[amo][] = "";
  descript[amo][] = "";


  //
  descript[item][] = "";

  //
  descript[kit][] = "";

  descript[gren][wind_gr] =
    "as if puppy poopy lets go a big fart. played team fortress, called it conc grenade";
};
