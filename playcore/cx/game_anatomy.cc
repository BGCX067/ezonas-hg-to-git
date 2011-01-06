class anatomy
{
  enum health_scale { SICK, FEVER, 2 };
  enum sound_scale { SILENT, IN_TOWN, OUTSIDE, NOISY_CROWD };
  enum sight_scale { FOGGY, NIGHT, DARK, DAY };
  enum sense_scale { near, obfuscated, normal, read };
  enum consc_scale { death, coma, knock, shake, normal, boost };
  // obfuscated both depends on envir but also on some specific items and fighting effects 

  // 0 = death
  int metabolism = 100;

  // -100 = 3min total loss of conscience, then disintegrated
  int health = NORMAL; 

  int sense = normal;

  int conscience = normal;
  // equivalent to an IA controlled game, to reflect one concentration (or mana)

  // when it hit 50, metabolism decreases, 1 point per 15min. IA became less controllable
  // ex: won't attack for 3min, go rogue, or wait to recover until 75 metabolism
  // at 25, specific spell bcome unavailable. IA go in standby mode, trying to hide to get rescued
  // they won't try to get in combat before replenish their full metabolism
  // a conscious character is required to achieve orders, depending of their needed grade
  // character's performance is only rated by evergy casting cost diminution of all spells, rather
  // than specific spell boost
  // this is to ensure the spell db can be modified freely without heavy game pre design
  int level; // starting to the 100 level, max 0
  // char [2][8]; //alias to the class plus its name

  void update_event()
  {
    if(metabolism == 0) game_over();
    if(!sense);
  }

}

