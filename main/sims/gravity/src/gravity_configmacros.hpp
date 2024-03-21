
/*
Enable All santiy checks.

--------------------------------------------------------
-fwarn-sanity-check-all
--------------------------------------------------------
*/
#define GRAVITY_SANITY_CHECK_ALL
//


/*
Enable Wavefront<->Phase connection sanity check.

--------------------------------------------------------
-fwarn-sanity-check-wavefront-floating

GWARN-SC-0001: Sanity Check of Wavefront Floating
--------------------------------------------------------
Report warning when a Wavefront is fired, but not connected to any downstream Phase.
The checks are ranged in the *current dimension*.

For example, if a Wavefront is fired in the X dimension, the check will be ranged in the X dimension.
When Phase that accepts the Wavefront sits in the A, B, C dimension, while excluding X, 
the check will report warning.
*/
#define GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING
//
#ifdef GRAVITY_SANITY_CHECK_ALL
#   define GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING
#endif
//
#ifdef GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING
#   define GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING__MESSAGE \
    "GWARN-SC-0001: Wavefront Floating: Wavefront is fired, but not collected by any downstream Phase."
#endif
//
