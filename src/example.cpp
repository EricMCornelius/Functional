#include "chain.hpp"
#include "functor.hpp"

#include <iostream>
#include <string>

struct request {
  std::string body = "Hello world";
};

struct parsed_request {
  parsed_request(const std::string& body_) : body(body_) { }

  std::string body;
};

template <typename Continuation>
void request_generator(const Continuation& cont) {
  request r;
  cont(std::move(r));
}
FunctorTemplate(request_generator, ReqGenerator);

template <typename Request, typename Continuation>
void request_parser(const Continuation& cont, Request&& request) {
  parsed_request p(request.body);
  p.body += "!";
  cont(std::move(p));
}
FunctorTemplate(request_parser, ReqParser);

template <typename Request, typename Continuation>
void request_parser2(const Continuation& cont, Request&& request) {
  request.body += "?";
  cont(std::forward<Request>(request));
}
FunctorTemplate(request_parser2, ReqParser2);

template <typename Request, typename Continuation>
void request_parser3(const Continuation& cont, Request&& request) {
  cont(1);
}
FunctorTemplate(request_parser3, ReqParser3);

template <typename Request, typename Continuation>
void request_printer(const Continuation& cont, const Request& request) {
  std::cout << request.body << std::endl;
  cont(request);
}
FunctorTemplate(request_printer, ReqPrinter);

struct ReqPrinter2 {
  template <typename Continuation, typename... Args>
  void operator () (const Continuation& cont, Args&&... args) const {
    std::cout << "Unmatched" << std::endl;
    cont(std::forward<Args>(args)...);
  }
  
  template <typename Continuation>
  void operator () (const Continuation& cont, request&& req) const {
    std::cout << "Unparsed: " << req.body << std::endl;
  }

  template <typename Continuation>
  void operator () (const Continuation& cont, parsed_request&& req) const {
    std::cout << "Parsed: " << req.body << std::endl;
  }
};

template <typename Continuation>
void request_printer3(const Continuation& cont, int val) {
  std::cout << val << std::endl;
}
FunctorTemplate(request_printer3, ReqPrinter3);

int main(int argc, char* argv[]) {
  chain<ReqGenerator, ReqParser, ReqPrinter> p2;
  p2();

  chain<ReqGenerator, ReqParser2, ReqPrinter> p3;
  p3();

  chain<ReqGenerator, ReqParser, ReqParser2, ReqPrinter> p4;
  p4();

  chain<ReqGenerator, ReqParser, ReqPrinter2> p5;
  p5();

  chain<ReqGenerator, ReqParser2, ReqPrinter2> p6;
  p6();

  chain<ReqGenerator, ReqParser3, ReqPrinter2, ReqPrinter3> p7;
  p7();
}


