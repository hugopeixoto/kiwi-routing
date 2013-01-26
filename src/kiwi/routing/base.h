/**
 * @file base.h
 * kiwi/http
 *
 * Copyright (c) 2013 Hugo Peixoto.
 * Distributed under the MIT License.
 */
#ifndef KIWI_ROUTING_BASE_H_
#define KIWI_ROUTING_BASE_H_

#include <string>
#include <list>
#include <map>
#include <functional>

#include "kiwi/routing/rule.h"
#include "kiwi/routing/method.h"

namespace kiwi {
  namespace routing {
    typedef std::function<void(void*)> Action;

    class RouteResult {
      public:
      virtual operator bool () const;
      virtual std::string operator[] (const char*) const;

      public:
      bool matched;
      std::map<std::string, std::string> parameters;
      Action action;
    };

    class Base {
      public:

      /**
       * @brief Destructor. Deletes all the rules.
       */
      // virtual ~Base ();

      public:
      typedef std::list<std::pair<Rule*, Action> > RuleList;

      /**
       * @brief Adds rules for a RESTful resource, identified by the given name.
       */
      template<typename Controller>
      Base& resources (const std::string& a_plural_resource_name);

      /**
       * @brief Maps the entry point of the application to a given controller/action.
       * This is equivalent to calling Base::map(GET, "/", a_action)
       */
      template<typename Controller>
      Base& root (void (Controller::*a_action)(void));

      /**
       * @brief Maps the given matching string to a controller and action.
       */
      template<typename Controller>
      Base& map (
        const Method& a_method,
        const std::string& a_match,
        void (Controller::*a_action)(void));


      public:
      /**
       * @brief Determines if the given method and URI match any rules.
       * If they do, the return object is filled with the match result.
       */
      RouteResult recognize_path (
        const Method& a_method,
        const std::string& a_uri);

      protected:
      std::map<Method, RuleList> rules_; //!< List of rules. To be replaced with a magic automata.
    };

    template<typename Controller>
    Base& Base::map (
      const Method& a_method,
      const std::string& a_match,
      void (Controller::*a_action)(void))
    {
      rules_[a_method].push_back(
        std::make_pair(new Rule(a_match), [=](void* a_data) {
          (Controller(a_data).*a_action)();
      }));

      return *this;
    }

    template<typename Controller>
    Base& Base::root (void (Controller::*a_action)(void))
    {
      return map(Method::GET, "/", a_action);
    }

    template<typename Controller>
    Base& Base::resources (const std::string& a_plural_resource_name)
    {
      std::string resource = a_plural_resource_name;

      return
        map(Method::GET, "/" + resource, &Controller::index).
        map(Method::POST, "/" + resource, &Controller::create).
        map(Method::PUT, "/" + resource + "/:id", &Controller::update).
        map(Method::DELETE, "/" + resource + "/:id", &Controller::destroy).
        map(Method::GET, "/" + resource + "/:id", &Controller::show);
    }
  }
}

#endif // KIWI_ROUTING_BASE_H_
