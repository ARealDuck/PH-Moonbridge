#ifndef OBSWSOPS_HPP
#define OBSWSOPS_HPP
enum class opcodes {
	Hello,
	Identify,
	Identified,
	Reidentify,
	Event,
	Request,
	RequestResponse,
	RequestBatch,
};
enum class closecodes {
	Dontclose,
	UnknownReason = 4002,
	MissingDataField = 4003,
	InvalidDataFieldType = 4004,
	InvalidDataFieldValue = 4005,
	UnknownOpCode = 4006,
	NotIdentified = 4007,
	AlreadyIdentified = 4008,
	AuthenticationFailed = 4009,
	UnsupportedRpcVersion = 4010,
	SessionInvalidated = 4011,
	UnsupportedFeature = 4012,
};
enum class requestbatchexetypes {
	None = -1,
	SerialRealtime,
	SerialFrame,
	Parallel,
};
enum class requeststatus {
	unknown = 0,
	NoError = 10,
	Success = 100,
	MissingRequestType = 203,
	UnknwonRequestType,
	GenericError,
	UnsupportedRequestBatchExecutionType,
	NotReady,
	MissingRequestField = 300,
	MissingRequestData,
	InvalidRequestField = 400,
	InvalidRequestFieldType,
	RequestFieldOutOfRange,
	RequestFieldEmpty,
	TooManyRequestFields,
	OutputRunning = 500,
	OutputNotRunning,
	OutputPaused,
	OutputNotPaused,
	OutputDisabled,
	StudioModeActivate,
	StudioModeNotActive,
	ResourceNotFound = 600,
	ResourceAlreadyExisits,
	InvalidResourceType,
	NotEnoughResources,
	InvalidResourceState,
	InvalidInputKind,
	ResourceNotConfigurable,
	InvalidFilterKind,
	ResourceCreationFailed = 700,
	ResourceActionFailed,
	RequestProcessingFailed,
	CannotAct,
};
enum class EventSub {
	General
};
class obswsops
{
public:
	static obswsops* obswsopsinit();
	static obswsops* instance;
	void closeobswsops();

private:
	obsws* obsws;
	obswsops();
	~obswsops();
	obswsops(const obswsops&) = delete;
	obswsops& operator=(const obswsops&) = delete;

};
#endif // !OBSWSOPS_HPP