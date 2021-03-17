#pragma once

namespace calcpp {
    enum class StatusCode {
        OK,
        INTERNAL,
    };

    class Status {
        StatusCode code;

        public:
        Status(StatusCode code) : code{code} {}

        inline bool ok() { return code == StatusCode::OK; }

        static Status& OK() {
            static Status ok_status(StatusCode::OK);
            return ok_status;
        }
    };
}  // namespace calcpp
