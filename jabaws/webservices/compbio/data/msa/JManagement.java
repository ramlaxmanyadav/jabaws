package compbio.data.msa;

import java.security.InvalidParameterException;

import javax.jws.WebParam;

import compbio.metadata.ChunkHolder;
import compbio.metadata.JobStatus;

public interface JManagement {

	/**
	 * Stop running the job <code>jobId</code> but leave its output untouched
	 * 
	 * @return true if job was cancelled successfully, false otherwise
	 * @throws InvalidParameterException
	 *             is thrown if jobId is empty or cannot be recognised e.g. in
	 *             invalid format
	 */
	boolean cancelJob(@WebParam(name = "jobId") String jobId);

	/**
	 * Return the status of the job.
	 * 
	 * @param jobId
	 *            - unique job identifier
	 * @return JobStatus - status of the job
	 * @throws InvalidParameterException
	 *             is thrown if jobId is empty or cannot be recognised e.g. in
	 *             invalid format
	 * @see JobStatus
	 */
	JobStatus getJobStatus(@WebParam(name = "jobId") String jobId);

	/**
	 * Reads 1kb chunk from the statistics file which is specific to a given web
	 * service from the <code>position</code>. If in time of a request less then
	 * 1kb data is available from the position to the end of the file, then it
	 * returns all the data available from the position to the end of the file.
	 * 
	 * @param jobId
	 *            - unique job identifier
	 * @param position
	 *            - next position within the file to read
	 * @return ChunkHolder - which contains a chunk of data and a next position
	 *         within the file from which no data has been read
	 * @throws InvalidParameterException
	 *             thrown if jobId is empty or cannot be recognised e.g. in
	 *             invalid format and also if the position value is negative
	 * @see ChunkHolder
	 */
	ChunkHolder pullExecStatistics(@WebParam(name = "jobId") String jobId,
			@WebParam(name = "position") long position);

}
