namespace Core::Versioning
{
    struct Version
    {
        Version() = default;
        Version(const Version& other) = default;

        Version& operator=(const Version& other) = default;

        virtual ~Version() = default;

    protected:
        friend bool operator==(const Version& v1, const Version& v2);
        friend bool operator<(const Version& v1, const Version& v2);

        virtual bool Equals(const Version& other) const = 0;
        virtual bool LessThan(const Version& other) const = 0;
    };

    template <typename T>
    struct IVersion : public Version
    {
    protected:
        friend bool operator==(const Version& v1, const Version& v2);
        friend bool operator<(const Version& v1, const Version& v2);
        
        bool Equals(const Version& other) const override
        {
            // will throw if not comparing correct types
            const T* t1 = dynamic_cast<const T*>(this);
            const T* t2 = dynamic_cast<const T*>(&other);

            if (t1 == nullptr || t2 == nullptr)
            {
                return false;
            }

            return t1->Equals(*t2);
        }

        // throws because relative comparison does not mean anything
        // for different version types
        bool LessThan(const Version& other) const override
        {
            // will throw if not comparing correct types
            const T& t1 = dynamic_cast<const T&>(*this);
            const T& t2 = dynamic_cast<const T&>(other);

            return t1.LessThan(t2);
        }
    };

    bool operator==(const Version& v1, const Version& v2)
    {
        return v1.Equals(v2);
    }

    bool operator!=(const Version& v1, const Version& v2)
    {
        return !(v1 == v2);
    }

    bool operator<(const Version& v1, const Version& v2)
    {
        return v1.LessThan(v2);
    }

    bool operator>(const Version& v1, const Version& v2)
    {
        return v2 < v1;
    }

    bool operator<=(const Version& v1, const Version& v2)
    {
        return !(v1 > v2);
    }

    bool operator>=(const Version& v1, const Version& v2)
    {
        return !(v1 < v2);
    }
}