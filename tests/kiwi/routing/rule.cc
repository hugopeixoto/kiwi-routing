/**
 * @file rule.cc
 * tests
 *
 * Copyright (c) 2013 Hugo Peixoto.
 * Distributed under the MIT License.
 */
#include "gtest/gtest.h"
#include "kiwi/routing/rule.h"

using kiwi::routing::Rule;
using kiwi::routing::MatchResult;

TEST(KiwiRoutingRule, ShouldMatchRootRoute)
{
    EXPECT_TRUE(Rule("/").matches("/"));
}

TEST(KiwiRoutingRule, ShouldNotMatchIfExpressionDiffers)
{
  EXPECT_TRUE(!Rule("/").matches("herp"));
}

TEST(KiwiRoutingRule, ShouldMatchARouteWithNoParameters)
{
  EXPECT_TRUE(Rule("/hello").matches("/hello"));
}

TEST(KiwiRoutingRule, ShouldntMatchIfTheRouteIsASubstringOfTheURI)
{
  EXPECT_TRUE(!Rule("/hello").matches("/hello_world"));
}

TEST(KiwiRoutingRule, ShouldMatchWithSingleParameter)
{
  EXPECT_TRUE(Rule("/hello/:target").matches("/hello/world"));
}

TEST(KiwiRoutingRule, ShouldntMatchWithSingleParameterIfNoneIsProvided)
{
  EXPECT_TRUE(!Rule("/hello/:target").matches("/hello"));
}

TEST(KiwiRoutingRule, ShouldntGlobEverythingIntoAParameter)
{
  EXPECT_TRUE(!Rule("/hello/:target").matches("/hello/world/from/peixoto"));
}

TEST(KiwiRoutingRule, ShouldAcceptMultipleParameters)
{
  EXPECT_TRUE(Rule("/hello/:target/from/:source").matches("/hello/world/from/peixoto"));
}

TEST(KiwiRoutingRule, ShouldFillParameters)
{
  MatchResult result = Rule("/hello/:target/from/:source").matches("/hello/world/from/peixoto");
  EXPECT_TRUE(result["source"] == "peixoto");
  EXPECT_TRUE(result["target"] == "world");
}

