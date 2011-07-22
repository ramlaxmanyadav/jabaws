package compbio.data.msa;

import java.util.Date;
import java.util.Set;

import javax.jws.WebService;

import compbio.ws.client.Services;

/**
 * JABAWS services registry
 * 
 * @author pvtroshin
 * @version 1.0 June 2011
 */
@WebService(targetNamespace = JABAService.V2_SERVICE_NAMESPACE)
public interface RegistryWS extends JABAService {

	/**
	 * List of services that are functioning on the server. This function
	 * returns the results of testing performed some time ago by
	 * {@link #testAllServices} or {@link #testService(Services)} methods. The
	 * time of last check can be obtained from
	 * {@link #getLastTestedOn(Services)} method
	 * 
	 * @return the Set of Services which are functioning on the server
	 * @see #testAllServices()
	 */
	Set<Services> getSupportedServices();
	/**
	 * Number of seconds since the last test. Returns 0 if the service was not
	 * tested or tested less then a one second ago.
	 * 
	 * @param service
	 * @return
	 */
	int getLastTested(Services service);
	/**
	 * The date and time the service has been verified to work last time
	 * 
	 * @param service
	 * @return the Date and time on which the service was last tested
	 */
	Date getLastTestedOn(Services service);
	/**
	 * Test all JABAWS services on the server
	 * 
	 * @return the test log
	 */
	String testAllServices();
	/**
	 * Test a particular service
	 * 
	 * @param service
	 * @return the testing log
	 */
	String testService(Services service);
	/**
	 * Check whether a particular web service is working on this server
	 * 
	 * @param service
	 * @return true if the service was functioning in time of last testing.
	 */
	boolean isOperating(Services service);

}
