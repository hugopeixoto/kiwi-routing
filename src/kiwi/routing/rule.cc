/**
 * @file rule.cc
 * kiwi/http
 *
 * Copyright (c) 2013 Hugo Peixoto.
 * Distributed under the MIT License.
 */
#include "kiwi/routing/rule.h"

using kiwi::routing::Rule;
using kiwi::routing::MatchResult;

MatchResult::operator bool () const
{
  return matched;
}

std::string MatchResult::operator[] (const char* a_key) const
{
  auto match = parameters.find(a_key);
  if (match == parameters.end()) {
    return "";
  } else {
    return match->second;
  }
}

