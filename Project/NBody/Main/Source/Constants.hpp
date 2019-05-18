#pragma once

#include "Utility.hpp"

/**
 * Closest particles to center in AU.
 */
const double INNER_BOUND = 0.3;

/**
 * Softens particles interactions at close distances. Distance expressed in meters.
 */
const double SOFTENING = Utility::astronomicalUnitsToMeters(0.015);

const double SOLAR_MASS = 2.0e30; // In kg

/**
 * AU (only applies when binary code uncommented).
 */
const double BINARY_SEPARATION = 0.07;

/**
 * Disk mask as a portion of center star/black hole mass.
 */
const double EXTRA_MASS = 1.5; // 0.02

/**
 * For experimentation only. Will probably cause weird results.
 */
const int ENABLE_FRICTION = 0;

/**
 * Only applies if friction is enabled.
 */
const double FRICTION_FACTOR = 25.0;

/**
 * Barnes-Hut Distance approximation factor.
 */
const double MAX_DISTANCE = 0.75; // 2.0

/**
 * The gravitational constant.
 */
const double G = 6.67408e-11;

/**
 * "Zoom" of images produced.
 */
const double RENDER_SCALE = 2.5;

const double MAX_VEL_COLOR = 40000.0; // In km/s

const double MIN_VEL_COLOR = 14000.0; // In km/s

const double PARTICLE_BRIGHTNESS = 0.35; // 0.03 for 256/512k, 0.4 for 16k

/**
 * Probably leave this alone.
 */
const double PARTICLE_SHARPNESS = 1.0;

/**
 * Simulated time between integration steps, in seconds.
 */
const int TIME_STEP = 3 * 32 * 1024; // (1*128*1024)

/**
 * Range of pixels to render.
 */
const int DOT_SIZE = 8; // 15

/**
 * Print lots of info to the console.
 */
const bool DEBUG_INFO = false;

/**
 * Thickness in AU
 */
const double SYSTEM_THICKNESS = 0.08;
