// states
#define MOVING  (1 << 0)
#define RUNNING (1 << 1)
#define FALLING (1 << 2)
#define STUNNED (1 << 3)
#define INVISIBLE (1 << 4)
#define STEALTH (1 << 5)
#define KNOCKED (1 << 6)
#define DEAD	(1 << 7)
#define	BLINDED	(1 << 8)

// events
#define JUMPS    (1 << 0)
#define LANDS    (1 << 1)
#define MOVES    (1 << 2)
#define STOPS    (1 << 3)
#define USE_ITEM (1 << 4)
// #define (1 << 5)
// #define (1 << 6)


// type mask
#define PLAYER (1 << 0) // player or MOB
// #define (1 << 1)
// #define (1 << 2)

// ability masks
#define ALLOW_MOVEMENT       (1 << 0)
#define TARGET_IN_FRONT      (1 << 1)
#define REQUIRES_TARGET      (1 << 2)
#define CLICK_LOCATION_EVENT (1 << 3)
#define SPLASH_DAMAGE        (1 << 4)

// #define (1 << 5)
// #define (1 << 6)
// #define (1 << 7)
// #define	(1 << 8)
// #define	(1 << 9)
// #define	(1 << 10)
// #define	(1 << 11)
// #define	(1 << 12)
// #define	(1 << 13)
// #define	(1 << 14)
// #define	(1 << 15)
// #define	(1 << 16)
// #define	(1 << 17)
// #define	(1 << 18)
// #define	(1 << 19)
// #define	(1 << 20)