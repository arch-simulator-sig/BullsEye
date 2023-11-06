#pragma once
//
//
//
//

#include <string>
#include <vector>
#include <initializer_list>


class CapturedError {
private:
    std::string                 source;
    std::string                 type;
    std::vector<std::string>    messages;

public:
    CapturedError() noexcept;
    CapturedError(const std::string& source) noexcept;
    CapturedError(const std::string& source, const std::string& type) noexcept;
    CapturedError(const std::string& source, const std::string& type, const std::vector<std::string>& messages) noexcept;
    CapturedError(const std::string& source, const std::string& type, std::initializer_list<std::string> messages) noexcept;

    const std::string&                          GetSource() const noexcept;
    void                                        SetSource(const std::string& source) noexcept;

    const std::string&                          GetType() const noexcept;
    void                                        SetType(const std::string& type) noexcept;

    const std::vector<std::string>&             GetMessages() const noexcept;
    void                                        SetMessages(const std::vector<std::string>& messages) noexcept;
    void                                        SetMessages(std::initializer_list<std::string> messages) noexcept;
    void                                        AppendMessage(const std::string& message) noexcept;

    size_t                                      GetMessageCount() const noexcept;

    std::vector<std::string>::iterator          begin() noexcept;
    std::vector<std::string>::iterator          end() noexcept;

    std::vector<std::string>::const_iterator    begin() const noexcept;
    std::vector<std::string>::const_iterator    end() const noexcept;
};


using CapturedErrors = std::vector<CapturedError>;
