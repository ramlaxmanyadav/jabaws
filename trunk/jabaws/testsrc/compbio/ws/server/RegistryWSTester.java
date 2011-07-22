package compbio.ws.server;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNotNull;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.fail;

import java.net.ConnectException;
import java.util.EnumSet;

import javax.xml.ws.WebServiceException;

import org.testng.annotations.Test;

import compbio.metadata.AllTestSuit;
import compbio.ws.client.Jws2Client;
import compbio.ws.client.Services;
import compbio.ws.client.WSTesterTester;

public class RegistryWSTester {

	@Test(groups = {AllTestSuit.test_group_webservices})
	public void testGetSupportedServices() {
		try {
			compbio.data.msa.RegistryWS reg = Jws2Client
					.connectToRegistry(WSTesterTester.SERVER);
			assertEquals(EnumSet.of(Services.AAConWS, Services.JronnWS,
					Services.MuscleWS, Services.ClustalWS),
					reg.getSupportedServices());
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}
	@Test(groups = {AllTestSuit.test_group_webservices})
	public void testTestService() {
		compbio.data.msa.RegistryWS reg = null;
		try {
			reg = Jws2Client.connectToRegistry(WSTesterTester.SERVER);
			assertNotNull(reg.testService(Services.AAConWS));
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}

	@Test(dependsOnMethods = {"testTestService"}, groups = {AllTestSuit.test_group_webservices})
	public void testIsOperating() {
		try {
			compbio.data.msa.RegistryWS reg = Jws2Client
					.connectToRegistry(WSTesterTester.SERVER);
			assertTrue(reg.isOperating(Services.AAConWS));
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}

	@Test(dependsOnMethods = {"testTestService"}, groups = {AllTestSuit.test_group_webservices})
	public void testGetLastTestedOn() {
		try {
			compbio.data.msa.RegistryWS reg = Jws2Client
					.connectToRegistry(WSTesterTester.SERVER);
			assertNotNull(reg.getLastTestedOn(Services.AAConWS));
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}

	@Test(dependsOnMethods = {"testTestService"}, groups = {AllTestSuit.test_group_webservices})
	public void testGetLastTested() {
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
			fail(e.getMessage());
		}
		try {
			compbio.data.msa.RegistryWS reg = Jws2Client
					.connectToRegistry(WSTesterTester.SERVER);
			System.out.println(reg.getLastTested(Services.AAConWS));
			assertTrue(reg.getLastTested(Services.AAConWS) > 0);
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}

	@Test(groups = {AllTestSuit.test_group_webservices})
	public void testTestAllServices() {
		try {
			compbio.data.msa.RegistryWS reg = Jws2Client
					.connectToRegistry(WSTesterTester.SERVER);
			System.out.println(reg.testAllServices());
		} catch (ConnectException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (WebServiceException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}
}
