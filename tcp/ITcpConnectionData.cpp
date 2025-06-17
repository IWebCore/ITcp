﻿#include "ITcpConnectionData.h"
#include "core/config/IProfileImport.h"
#include "core/unit/IFixedArrayMemoryPoolUnit.h"
#include "http/IHttpConstant.h"

$PackageWebCoreBegin

namespace detail
{
    static IFixedArrayMemoryPoolUnit<char, IHttp::HTTP_BASE_MESSAGE_SIZE> s_pool {};
}

ITcpConnectionData::ITcpConnectionData()
    : m_data(detail::s_pool.allocateArray())
{
}

ITcpConnectionData::~ITcpConnectionData()
{
    detail::s_pool.deallocateArray(m_data);
}

IStringView ITcpConnectionData::getBufferView(std::size_t length)
{
    if(length == std::string_view::npos){
        length = m_buffer.size();
    }
    return IStringView(static_cast<const char*>(m_buffer.data().data()), length);
}

IStringView ITcpConnectionData::getUnResolvedDataView()
{
    return IStringView(m_data + m_parsedSize, m_readSize-m_parsedSize);
}

IStringView ITcpConnectionData::readBy(std::size_t length)
{
    IStringView view(m_data + m_parsedSize, length);
    m_parsedSize += length;
    return view;
}

IStringView ITcpConnectionData::readLine()
{
    auto line = find(IHttp::NEW_LINE);
    IStringView view(m_data + m_parsedSize, line);
    m_parsedSize += line;
    return view;
}

IStringView ITcpConnectionData::readPartition()
{
    auto length = find(IHttp::NEW_PART);
    IStringView view(m_data + m_parsedSize, length);
    m_parsedSize += length;
    return view;
}

std::size_t ITcpConnectionData::find(IStringView view)
{
    auto data = std::string_view(m_data + m_parsedSize, getUnparsedLength());
    auto pos = data.find(view);
    return (pos == std::string_view::npos) ? 0 : pos + view.length();
}

std::size_t ITcpConnectionData::getUnparsedLength() const
{
    return m_readSize-m_parsedSize;
}

$PackageWebCoreEnd
