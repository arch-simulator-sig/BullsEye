#include "appmain_err.hpp"
//
//
//
//


// Implementation of: class CapturedError
/*
std::string                 source;
std::string                 type;
std::vector<std::string>    messages;
*/

CapturedError::CapturedError() noexcept
    : source    ()
    , type      ()
    , messages  ()
{ }

CapturedError::CapturedError(const std::string& source) noexcept
    : source    (source)
    , type      ()
    , messages  ()
{ }

CapturedError::CapturedError(const std::string& source, const std::string& type) noexcept
    : source    (source)
    , type      (type)
    , messages  ()
{ }

CapturedError::CapturedError(const std::string& source, const std::string& type, const std::vector<std::string>& messages) noexcept
    : source    (source)
    , type      (type)
    , messages  (messages)
{ }

CapturedError::CapturedError(const std::string& source, const std::string& type, std::initializer_list<std::string> messages) noexcept
    : source    (source)
    , type      (type)
    , messages  (messages)
{ }

const std::string& CapturedError::GetSource() const noexcept
{
    return this->source;
}

void CapturedError::SetSource(const std::string& source) noexcept
{
    this->source = source;
}

const std::string& CapturedError::GetType() const noexcept
{
    return this->type;
}

void CapturedError::SetType(const std::string& type) noexcept
{
    this->type = type;
}

const std::vector<std::string>& CapturedError::GetMessages() const noexcept
{
    return this->messages;
}

void CapturedError::SetMessages(const std::vector<std::string>& messages) noexcept
{
    this->messages = messages;
}

void CapturedError::SetMessages(std::initializer_list<std::string> messages) noexcept
{
    this->messages = messages;
}

void CapturedError::AppendMessage(const std::string& message) noexcept
{
    this->messages.push_back(message);
}

size_t CapturedError::GetMessageCount() const noexcept
{
    return this->messages.size();
}

std::vector<std::string>::iterator CapturedError::begin() noexcept
{
    return this->messages.begin();
}

std::vector<std::string>::iterator CapturedError::end() noexcept
{
    return this->messages.end();
}

std::vector<std::string>::const_iterator CapturedError::begin() const noexcept
{
    return this->messages.begin();
}

std::vector<std::string>::const_iterator CapturedError::end() const noexcept
{
    return this->messages.end();
}

