/**
 * @file method.h
 * kiwi/http
 *
 * Copyright (c) 2013 Hugo Peixoto.
 * Distributed under the MIT License.
 */
#ifndef KIWI_ROUTING_METHOD_H_
#define KIWI_ROUTING_METHOD_H_

namespace kiwi {
  namespace routing {
    enum class Method {
      GET,
      POST,
      PUT,
      DELETE,
      HEAD
    };
  }
}

#endif // KIWI_ROUTING_METHOD_H_
