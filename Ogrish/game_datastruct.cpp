#include "stdafx.h"


// ############# ABILITY EVENT #############
Event::Event(int _emitter_id, int _target_id, int _abil_state_id): // ability event constructor
type(ABILITY)//,
{ emitter_id = _emitter_id; ev_abil.target_id = _target_id; ev_abil.abil_state_id = _abil_state_id; }

// ############# ITEM EVENT #############
Event::Event(int _emitter_id, int _item_id): // ability event constructor
type(USE_ITEM)//,
{ emitter_id = _emitter_id; ev_item.item_id = _item_id; }


