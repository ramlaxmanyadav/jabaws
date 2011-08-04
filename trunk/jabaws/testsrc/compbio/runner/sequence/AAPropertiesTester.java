package compbio.runner.sequence;


import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNotNull;
import static org.testng.Assert.fail;

import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import compbio.data.sequence.ScoreManager;
import compbio.engine.Configurator;
import compbio.engine.client.ConfiguredExecutable;
import compbio.engine.client.Executable;
import compbio.engine.local.LocalRunner;
import compbio.metadata.AllTestSuit;
import compbio.metadata.JobExecutionException;
import compbio.metadata.JobSubmissionException;
import compbio.metadata.ResultNotAvailableException;

public class AAPropertiesTester {
	private AAProperties aaproperties;
	public static String test_outfile = "TO1381.aaproperties.out";

	@BeforeMethod(alwaysRun = true)
	void init() {
		aaproperties = new AAProperties();
		aaproperties.setInput(AllTestSuit.test_input).setOutput(test_outfile);
	}
	
	@Test(groups = {AllTestSuit.test_group_runner})
	public void testRunLocally() {
		try {
			ConfiguredExecutable<AAProperties> confJronn = Configurator.configureExecutable(aaproperties, Executable.ExecProvider.Local);
			// For local execution use relative
			LocalRunner lr = new LocalRunner(confJronn);
			lr.executeJob();
			ConfiguredExecutable<?> al1 = lr.waitForResult();
			assertNotNull(al1.getResults());
			ScoreManager al2 = confJronn.getResults();
			assertNotNull(al2);
			assertEquals(al2.asMap().size(), 3);
			assertEquals(al1.getResults(), al2);
		} catch (JobSubmissionException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (ResultNotAvailableException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		} catch (JobExecutionException e) {
			e.printStackTrace();
			fail(e.getLocalizedMessage());
		}
	}
}
