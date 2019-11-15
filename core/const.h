#pragma once

#ifndef CONST_H
#define CONST_H

#define LL long long
#define UI unsigned int

const int BASE_BIT = 32;
const LL BASE = 1LL << BASE_BIT;
const UI MAX_IN_BIT = BASE - 1;
const int MAX_LEN = 9000 / BASE_BIT;

const UI MAX_RAND_INTEGER = 1 << 30;

const char OUT[] = "0123456789ABCDEF";

const int NUMBER_THREAD = 8;

#endif