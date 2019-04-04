#pragma once

#include <string>
#include <sstream>

#include <ignite/ignite.h>
#include <ignite/ignition.h>

struct Widget {
    Widget() : id(0), width(0), height(0)
    {}

    Widget(int64_t _id, const std::string &_name, const std::string &_content, int _width, int _height)
        : id(_id), name(_name), content(_content), width(_width), height(_height)
    {}

    std::string toString() const
    {
        std::ostringstream oss;
        oss << "Widget [id=" << id
            << ", name=" << name
            << ", content=" << content
            << ", width=" << width
            << ", height=" << height
            << "]";
        return oss.str();
    }

    int64_t id;
    std::string name;
    std::string content;
    int width;
    int height;
};

namespace ignite { namespace binary {
template<>
struct BinaryType<Widget>
{
    static int32_t GetTypeId()
    {
        return GetBinaryStringHashCode("Widget");
    }

    static void GetTypeName(std::string& dst)
    {
        dst = "Widget";
    }

    static int32_t GetFieldId(const char* name)
    {
        return GetBinaryStringHashCode(name);
    }

    static int32_t GetHashCode(Widget& obj)
    {
        return 0;
    }

    static bool IsNull(Widget obj)
    {
        return false;
    }

    static void GetNull(Widget& dst)
    {
        dst = Widget();
    }

    static void Write(BinaryWriter& writer, const Widget& obj)
    {
        writer.WriteInt64("id", obj.id);
        writer.WriteString("name", obj.name);
        writer.WriteString("content", obj.content);
        writer.WriteInt32("width", obj.width);
        writer.WriteInt32("height", obj.height);
    }

    static void Read(BinaryReader& reader, Widget& dst)
    {
        dst.id = reader.ReadInt64("id");
        dst.name = reader.ReadString("name");
        dst.content = reader.ReadString("content");
        dst.width = reader.ReadInt32("width");
        dst.height = reader.ReadInt32("height");
    }
};
}}
