#ifndef WORKERDATA_HPP
#define WORKERDATA_HPP

#include "Worker.hpp"

enum EventType {
	CLIENTEVENT,
	CGIEVENT
};

class WorkerData {
	private:
		Request	&request;
		Response &response;
		CgiHandler &cgi;
		EventType event;

	public:
		WorkerData(Request &request, Response &response, CgiHandler &cgi, EventType event);
		~WorkerData();

		Request& getRequest(void);
		Response& getResponse(void);
		CgiHandler& getCgiHandler(void);
		EventType getEventType(void) const;
};

#endif
