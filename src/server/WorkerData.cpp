#include "../../inc/WorkerData.hpp"

WorkerData::WorkerData(Request &request, Response &response, CgiHandler &cgi, EventType event)
	: request(request), response(response), cgi(cgi) {
	this->event = event;
}

WorkerData::~WorkerData() {}

Request& WorkerData::getRequest()
{
	return (this->request);
}

Response& WorkerData::getResponse()
{
	return (this->response);
}

CgiHandler& WorkerData::getCgiHandler()
{
	return (this->cgi);
}

EventType WorkerData::getEventType() const
{
	return (this->event);
}