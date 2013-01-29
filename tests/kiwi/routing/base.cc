/**
 * @file base.cc
 * tests
 *
 * Copyright (c) 2013 Hugo Peixoto.
 * Distributed under the MIT License.
 */
#include "gtest/gtest.h"
#include "kiwi/routing/base.h"
#include "kiwi/routing/method.h"

using kiwi::routing::Method;
using kiwi::routing::Base;

class Controller {
  public:
  Controller (void*) {}
  void index () {}
};

class RestfulController {
  public:
  RestfulController (void*) {}

  void index () {}
  void show () {}
  void update () {}
  void create () {}
  void destroy () {}
};

TEST(KiwiRoutingBase, ShouldMapGETRoot)
{
  Base().map(Method::GET, "/", &Controller::index);
}

TEST(KiwiRoutingBase, ShouldChainWhenUsingMap)
{
  Base base;
  EXPECT_EQ(&base, &base.
     map(Method::GET, "/", &Controller::index).
     map(Method::POST, "/", &Controller::index));
}

TEST(KiwiRoutingBase, ShouldRespondToRecognizePath)
{
  Base().recognize_path(Method::GET, "/");
}

TEST(KiwiRoutingBase, ShouldRecognizePath)
{
  EXPECT_TRUE(Base().
    map(Method::GET, "/", &Controller::index).
    recognize_path(Method::GET, "/"));
}

TEST(KiwiRoutingBase, ShouldntRecognizeWithoutMap)
{
  EXPECT_TRUE(!Base().
    recognize_path(Method::GET, "/"));
}

TEST(KiwiRoutingBase, ShouldntRecognizeIfRuleDoesntMatch)
{
  EXPECT_TRUE(!Base().
    map(Method::GET, "/", &Controller::index).
    recognize_path(Method::GET, "/no-match"));
}

TEST(KiwiRoutingBase, ShouldntRecognizeIfMethodsDiffer)
{
  EXPECT_TRUE(!Base().
    map(Method::GET, "/", &Controller::index).
    recognize_path(Method::POST, "/"));
}

TEST(KiwiRoutingBase, ShouldReturnParameters)
{
  EXPECT_EQ("world", Base().
    map(Method::POST, "/hello/:from", &Controller::index).
    recognize_path(Method::POST, "/hello/world")["from"]);
}

TEST(KiwiRoutingBase, ShouldReturnRouteAction)
{
  (void)Base().
    map(Method::GET, "/", &Controller::index).
    recognize_path(Method::GET, "/").action;
}

TEST(KiwiRoutingBase, ShouldReturnCorrectRouteAction)
{
  struct C { C (void*) {} void index () { throw true; } };
  bool executed = false;

  try {
    Base().map(Method::GET, "/", &C::index).
      recognize_path(Method::GET, "/").action(NULL);
  } catch (bool success) {
    executed = success;
  }

  EXPECT_TRUE(executed);
}

TEST(KiwiRoutingBase, ShouldHaveRootAlias)
{
  (void)Base().root(&Controller::index);
}

TEST(KiwiRoutingBase, ShouldChainWhenUsingRoot)
{
  Base base;
  EXPECT_EQ(&base, &base.root(&Controller::index));
}

TEST(KiwiRoutingBase, ShouldRecognizeRoot)
{
  EXPECT_TRUE(Base().
    root(&Controller::index).
    recognize_path(Method::GET, "/"));
}

TEST(KiwiRoutingBase, ShouldRespondToResources)
{
  (void)Base().resources<RestfulController>("posts");
}

TEST(KiwiRoutingBase, ShouldChainWhenUsingResources)
{
  Base base;
  EXPECT_EQ(&base, &base.resources<RestfulController>("posts"));
}

TEST(KiwiRoutingBase, ShouldRecognizeResourcesIndex)
{
  EXPECT_TRUE(Base().
    resources<RestfulController>("posts").
    recognize_path(Method::GET, "/posts"));
}

TEST(KiwiRoutingBase, ShouldRecognizeResourcesShow)
{
  EXPECT_TRUE(Base().
    resources<RestfulController>("posts").
    recognize_path(Method::GET, "/posts/42"));
}

TEST(KiwiRoutingBase, ShouldRecognizeResourcesUpdate)
{
  EXPECT_TRUE(Base().
    resources<RestfulController>("posts").
    recognize_path(Method::PUT, "/posts/42"));
}

TEST(KiwiRoutingBase, ShouldRecognizeResourcesCreate)
{
  EXPECT_TRUE(Base().
    resources<RestfulController>("posts").
    recognize_path(Method::POST, "/posts"));
}

TEST(KiwiRoutingBase, ShouldRecognizeResourcesDestroy)
{
  EXPECT_TRUE(Base().
    resources<RestfulController>("posts").
    recognize_path(Method::DELETE, "/posts/42"));
}

